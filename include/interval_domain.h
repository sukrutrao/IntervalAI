#ifndef INTERVAL_DOMAIN_H
#define INTERVAL_DOMAIN_H

#include <cstdint>
#include <utility>

namespace intervalai {
	
typedef std::int32_t INT;

class Interval {

private:
	bool is_bot;
	INT low;
	INT high;
	void invariant();
public:
	Interval(bool is_bot = false);
	Interval(INT, INT);
	Interval(const Interval&);
	Interval operator+(const Interval&);
	Interval operator-(const Interval&);
	Interval operator*(const Interval&);
	Interval operator/(const Interval&);
	Interval operator-();
	Interval operator&(const Interval&);
	Interval operator|(const Interval&);
	static inline std::pair<INT, INT> get_limits();
};

}

#endif
