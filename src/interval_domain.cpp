#include "interval_domain.h"

#include <limit>
#include <cmath>

Interval::Interval() {
	limits = std::make_pair(std::numeric_limits<INT>::min()/2, 
						std::numeric_limits<INT>::max()/2);
	low = limits.first;
	high = limits.second;
	invariant();
}

Interval::Interval(INT low, INT high) {
	limits = std::make_pair(std::numeric_limits<INT>::min()/2, 
						std::numeric_limits<INT>::max()/2);
	this->low = low;
	this->high = high;
	invariant();
}

inline std::pair<INT, INT> Interval::get_limits() {
	return limits;
}

void Interval::invariant() {
	assert(low <= high);
	assert(low >= limits.first);
	assert(high <= limits.second);
}

Interval Interval::operator+(const Interval& other) {
	Interval result;
	result.low = this->low + other.low;
	result.high = this->high + other.high;
	result.invariant();
	return result;
}

Interval Interval::operator-(const Interval& other) {
	return (*this) + (-other);
}

Interval Interval::operator*(const Interval& other) {
	Interval result;
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
			result.low = min(this->low * other.high, this->high * other.low);
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
	result.low = -(this->high);
	result.high = -(this->low); 
	invariant();
	return result;
}
