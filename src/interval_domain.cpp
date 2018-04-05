#include "interval_domain.h"

#include <limits>
#include <cmath>
#include <cassert>
#include <algorithm>

using namespace intervalai;
using std::min;
using std::max;

Interval::Interval(bool is_bot) {
	this->is_bot = is_bot;
	std::pair<INT, INT> limits = get_limits();
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

Interval::Interval(const Interval& other) {
	this->is_bot = other.is_bot;
	this->low = other.low;
	this->high = other.high;
}

inline std::pair<INT, INT> Interval::get_limits() {
	return std::make_pair(std::numeric_limits<INT>::min()/2, 
						std::numeric_limits<INT>::max()/2);
}

void Interval::invariant() {
	if(is_bot) return;
	assert(low <= high);
	std::pair<INT, INT> limits = get_limits();
	if(low < limits.first) low = limits.first;
	if(high > limits.second) high = limits.second;
}

Interval Interval::operator+(const Interval& other) {
	Interval result;
	if(this->is_bot || other.is_bot) {
		result.is_bot = true;
		return result;
	}
	result.low = this->low + other.low;
	result.high = this->high + other.high;
	result.invariant();
	return result;
}

Interval Interval::operator-(const Interval& other) {
	return operator+(operator-(other));
}

Interval Interval::operator*(const Interval& other) {
	Interval result;
	if(this->is_bot || other.is_bot) {
		result.is_bot = true;
		return result;
	}
	if(this->low > 0 && other.low > 0) {
		result.low = this->low * other.low;
		result.high = this->high * other.high;
	} else if(this->low > 0 && other.low <= 0) {
		if(other.high > 0) {
			result.low = this->high * other.low;
			result.high = this->high * other.high;
		} else {
			result.low = this->high * other.low;
			result.high = this->low * other.high;
		}
	} else if(this->low <= 0 && other.low > 0) {
		if(this->high > 0) {
			result.low = this->low * other.high;
			result.high = this->low * other.low;
		} else {
			result.low = this->low * other.high;
			result.high = this->high * other.low;
		}
	} else {
		if(this->high > 0 && other.high > 0) {
			result.low=std::min(this->low * other.high, this->high * other.low);
			result.high = this->high * other.high;
		} else if(this->high > 0 && other.high <= 0) {
			result.low = other.low * this->high;
			result.high = this->low * other.high;
		} else if(this->high <= 0 && other.high > 0) {
			result.low = this->low * other.high;
			result.high = other.low * this->high;
		} else {
			result.low = this->high * other.high;
			result.high = this->low * other.low;
		}
	}
	invariant();
	return result;
}

Interval Interval::operator-() {
	Interval result;
	if(this->is_bot) {
		result.is_bot = true;
		return result;
	}
	result.low = -(this->high);
	result.high = -(this->low); 
	invariant();
	return result;
}

// Meet
Interval Interval::operator&(const Interval& other) {
	Interval result;
	if(this->is_bot || other.is_bot) {
		result.is_bot = true;
	} else if(this->high < other.low || other.high < this->low) {
		result.is_bot = true;
	} else {
		result.low = max(this->low, other.low);
		result.high = min(this->high, other.high);
	}
	invariant();
	return result;
}

// Join
Interval Interval::operator|(const Interval& other) {
	Interval result;
	if(this->is_bot) {
		result = other;
	} else if(other.is_bot) {
		result = *this;
	} else {
		result.low = min(this->low, other.low);
		result.high = max(this->high, other.high);
	}
	invariant();
	return result;
}
