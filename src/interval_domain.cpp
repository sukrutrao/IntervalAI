#include "interval_domain.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

using namespace intervalai;
using std::max;
using std::min;

Interval::Interval(bool is_bot) {
    this->is_bot = is_bot;
    std::pair<INT, INT> limits = top_limits();
    low = limits.first;
    high = limits.second;
    invariant();
}

Interval::Interval(INT low, INT high) {
    is_bot = false;
    this->low = low;
    this->high = high;
    invariant();
}

Interval::Interval(std::pair<INT, INT> interval_limits) {
    is_bot = false;
    this->low = interval_limits.first;
    this->high = interval_limits.second;
    invariant();
}

Interval::Interval(const Interval &other) {
    this->is_bot = other.is_bot;
    this->low = other.low;
    this->high = other.high;
}

void Interval::view() const { std::cout << to_string(); }

std::string Interval::to_string() const {
    std::string result;
    if (is_bot) {
        result = "Bot";
        return result;
    }
    result += "[";
    auto limits = top_limits();
    if (low == limits.first) {
        result += "-inf";
    } else if (low == limits.second) {
        result += "inf";
    } else {
        result += std::to_string(low);
    }
    result += ", ";
    if (high == limits.first) {
        result += "-inf";
    } else if (high == limits.second) {
        result += "inf";
    } else {
        result += std::to_string(high);
    }
    result += "]";
    return result;
}

inline INT Interval::max_value() {
    return static_cast<INT>(std::numeric_limits<DOMAIN_INT>::max());
}

inline INT Interval::min_value() {
    return static_cast<INT>(std::numeric_limits<DOMAIN_INT>::min());
}

inline std::pair<INT, INT> Interval::get_limits() {
    return std::make_pair(min_value(), max_value());
}

inline std::pair<INT, INT> Interval::top_limits() {
    return std::make_pair(ninf(), pinf());
}

void Interval::invariant() {
    if (is_bot)
        return;
    assert(low <= high);
    std::pair<INT, INT> limits = top_limits();
    if (low < limits.first)
        low = limits.first;
    if (high > limits.second)
        high = limits.second;
    if (low > limits.second) {
        low = limits.second;
    }
    if (high < limits.first) {
        high = limits.first;
    }
    assert(low <= high);
}

Interval Interval::operator+(const Interval &other) const {
    Interval result;
    if (this->is_bot || other.is_bot) {
        result.is_bot = true;
        return result;
    }
    result.low = this->low + other.low;
    result.high = this->high + other.high;
    result.invariant();
    return result;
}

Interval Interval::operator-(const Interval &other) const {
    return operator+(-other);
}

Interval Interval::operator*(const Interval &other) const {
    Interval result;
    if (this->is_bot || other.is_bot) {
        result.is_bot = true;
    } else {
        result.low =
            std::min({this->low * other.low, this->low * other.high,
                      this->high * other.low, this->high * other.high});
        result.high =
            std::max({this->low * other.low, this->low * other.high,
                      this->high * other.low, this->high * other.high});
    }
    result.invariant();
    return result;
}

Interval Interval::operator/(const Interval &other) const {
    Interval result;
    if (this->is_bot || other.is_bot) {
        result.is_bot = true;
    } else if (!(other.low <= 0 && other.high >= 0)) {
        result.low =
            std::min({this->low / other.low, this->low / other.high,
                      this->high / other.low, this->high / other.high});
        result.high =
            std::max({this->low / other.low, this->low / other.high,
                      this->high / other.low, this->high / other.high});
    } else {
        result = Interval();
    }
    result.invariant();
    return result;
}

Interval Interval::operator-() const {
    Interval result;
    if (this->is_bot) {
        result.is_bot = true;
    } else {
        result.low = -(this->high);
        result.high = -(this->low);
    }
    result.invariant();
    return result;
}

Interval Interval::operator+(INT other) const {
    return operator+(Interval(other, other));
}

Interval Interval::operator-(INT other) const {
    return operator-(Interval(other, other));
}

Interval Interval::operator*(INT other) const {
    return operator*(Interval(other, other));
}

Interval Interval::operator/(INT other) const {
    return operator/(Interval(other, other));
}

// Meet
Interval Interval::operator&(const Interval &other) const {
    Interval result;
    if (this->is_bot || other.is_bot) {
        result.is_bot = true;
    } else if (this->high < other.low || other.high < this->low) {
        result.is_bot = true;
    } else {
        result.low = max(this->low, other.low);
        result.high = min(this->high, other.high);
    }
    result.invariant();
    return result;
}

// Join
Interval Interval::operator|(const Interval &other) const {
    Interval result;
    if (this->is_bot) {
        result = other;
    } else if (other.is_bot) {
        result = *this;
    } else {
        result.low = min(this->low, other.low);
        result.high = max(this->high, other.high);
    }
    result.invariant();
    return result;
}

// cannot rely on answer if interval is bot
INT Interval::lowest_magnitude() {
    if (is_bot) {
        return 0;
    } else if (low < 0 && high < 0) {
        return high;
    } else if (low > 0 && high > 0) {
        return low;
    } else {
        return 0;
    }
}

bool Interval::isTop() {
    auto limits = top_limits();
    if (!is_bot && limits.first == low && limits.second == high) {
        return true;
    }
    return false;
}

bool Interval::isBot() { return is_bot; }

inline INT Interval::length() const {
    if (is_bot) {
        return 0;
    }
    return high - low;
}

// must be used only when not bot
std::pair<INT, INT> Interval::getInterval() {
    return std::make_pair(low, high);
}

tribool Interval::operator<(const Interval &other) const {
    if (this->is_bot || other.is_bot) {
        return tribool::False;
    }
    if (this->high < other.low) {
        return tribool::True;
    }
    Interval meet = operator&(other);
    if (meet.is_bot)
        return tribool::False;
    return tribool::Unknown;
}

tribool Interval::operator>(const Interval &other) const {
    return other.operator<(*this);
}

tribool Interval::operator==(const Interval &other) const {
    if (this->is_bot || other.is_bot) {
        return tribool::False;
    }
    Interval meet = operator&(other);
    if (meet.is_bot) {
        return tribool::False;
    }
    if (this->length() == 0 && other.length() == 0 && this->low == other.low) {
        return tribool::True;
    }
    return tribool::Unknown;
}

tribool Interval::operator!=(const Interval &other) const {
    return !(operator==(other));
}

tribool intervalai::operator&&(tribool first, tribool second) {
    if (first == tribool::True && second == tribool::True) {
        return tribool::True;
    } else if (first == tribool::False || second == tribool::False) {
        return tribool::False;
    }
    return tribool::Unknown;
}

tribool intervalai::operator||(tribool first, tribool second) {
    if (first == tribool::True || second == tribool::True) {
        return tribool::True;
    } else if (first == tribool::Unknown && second == tribool::Unknown) {
        return tribool::Unknown;
    }
    return tribool::False;
}

tribool intervalai::operator!(tribool first) {
    if (first == tribool::True) {
        return tribool::False;
    } else if (first == tribool::False) {
        return tribool::True;
    }
    return tribool::Unknown;
}

tribool Interval::operator<=(const Interval &other) const {
    return operator<(other) || operator==(other);
}

tribool Interval::operator>=(const Interval &other) const {
    return operator>(other) || operator==(other);
}

tribool Interval::operator<(INT other) const {
    return operator<(Interval(other, other));
}

tribool Interval::operator>(INT other) const {
    return operator>(Interval(other, other));
}

tribool Interval::operator==(INT other) const {
    return operator==(Interval(other, other));
}

tribool Interval::operator<=(INT other) const {
    return operator<=(Interval(other, other));
}

tribool Interval::operator>=(INT other) const {
    return operator>=(Interval(other, other));
}

tribool Interval::operator!=(INT other) const { return !(operator==(other)); }

inline INT Interval::pinf() { return max_value() + 1; }

inline INT Interval::ninf() { return min_value() - 1; }