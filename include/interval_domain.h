#ifndef INTERVAL_DOMAIN_H
#define INTERVAL_DOMAIN_H

#include <iostream>

namespace intervalai {
	
typedef int32_t INT;

class Interval {

private:
	INT low;
	INT high;
	const std::pair<INT, INT> limits;
	void invariant();
public:
	Interval();
	Interval(INT, INT);
	Interval operator+(const &Interval);
	Interval operator-(const &Interval);
	Interval operator*(const &Interval);
	Interval operator/(const &Interval);
	Interval operator-();
	std::pair<INT, INT> get_limits();
};

}

#endif
