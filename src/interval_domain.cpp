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

void Interval::view() {
    if (is_bot) {
        std::cout << "Bot";
        return;
    }
    std::cout << "[";
    auto limits = top_limits();
    if (low == limits.first) {
        std::cout << "-infty";
    } else if (low == limits.second) {
        std::cout << "infty";
    } else {
        std::cout << low;
    }
    std::cout << ", ";
    if (high == limits.first) {
        std::cout << "-infty";
    } else if (high == limits.second) {
        std::cout << "infty";
    } else {
        std::cout << high;
    }
    std::cout << "]";
}

inline std::pair<INT, INT> Interval::get_limits() {
    return std::make_pair(min_value(), max_value());
}

inline std::pair<INT, INT> Interval::top_limits() {
    return std::make_pair(min_value() - 1, max_value() + 1);
}

inline INT Interval::max_value() {
    return std::numeric_limits<DOMAIN_INT>::max();
}

inline INT Interval::min_value() {
    return std::numeric_limits<DOMAIN_INT>::min();
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
    // Check - TODO
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
    } else if (this->low > 0 && other.low > 0) {
        result.low = this->low * other.low;
        result.high = this->high * other.high;
    } else if (this->low > 0 && other.low <= 0) {
        if (other.high > 0) {
            result.low = this->high * other.low;
            result.high = this->high * other.high;
        } else {
            result.low = this->high * other.low;
            result.high = this->low * other.high;
        }
    } else if (this->low <= 0 && other.low > 0) {
        if (this->high > 0) {
            result.low = this->low * other.high;
            result.high = this->low * other.low;
        } else {
            result.low = this->low * other.high;
            result.high = this->high * other.low;
        }
    } else {
        if (this->high > 0 && other.high > 0) {
            result.low =
                std::min(this->low * other.high, this->high * other.low);
            result.high = this->high * other.high;
        } else if (this->high > 0 && other.high <= 0) { // TODO -check
            result.low = other.low * this->high;
            result.high = this->low * other.high;
        } else if (this->high <= 0 && other.high > 0) {
            result.low = this->low * other.high;
            result.high = other.low * this->low;
        } else {
            result.low = this->high * other.high;
            result.high = this->low * other.low;
        }
    }
    result.invariant();
    return result;
}

// Interval Interval::operator/(const Interval &other) {
//     Interval result;
//     if (this->is_bot || other.is_bot) {
//         result.is_bot = true;
//     } else if() {
//         result.low = this->low /
//     }
// }

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

Interval Interval::operator+(INT other) {
    Interval result;
    if (this->is_bot) {
        result.is_bot = true;
    } else {
        result.low = this->low + other;
        result.high = this->high + other;
    }
    result.invariant();
    return result;
}

Interval Interval::operator-(INT other) {
    Interval result;
    if (this->is_bot) {
        result.is_bot = true;
    } else {
        result.low = this->low - other;
        result.high = this->high - other;
    }
    result.invariant();
    return result;
}

Interval Interval::operator*(INT other) {
    Interval result;
    if (this->is_bot) {
        result.is_bot = true;
    } else if (other > 0) {
        result.low = this->low * other;
        result.high = this->high * other;
    } else {
        result.low = this->high * other;
        result.high = this->low * other;
    }
    result.invariant();
    return result;
}

Interval Interval::operator/(INT other) {
    Interval result;
    if (this->is_bot) {
        result.is_bot = true;
    } else if (other > 0) {
        result.low = this->low / other;
        result.high = this->high / other;
    } else {
        result.low = this->high / other;
        result.high = this->low / other;
    }
    result.invariant();
    return result;
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
    return tribool::False;
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
    return tribool::False;
}