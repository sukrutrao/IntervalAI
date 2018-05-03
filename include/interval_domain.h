#ifndef INTERVAL_DOMAIN_H
#define INTERVAL_DOMAIN_H

#include <cstdint>
#include <utility>

namespace intervalai {

typedef std::int64_t INT;
typedef std::int32_t DOMAIN_INT;

enum class tribool { True, False, Unknown };

class Interval {

  private:
    bool is_bot;
    INT low;
    INT high;
    void invariant();
    INT lowest_magnitude();

  public:
    Interval(bool is_bot = false);
    Interval(INT, INT);
    Interval(std::pair<INT, INT>);
    Interval(const Interval &);

    void view();

    Interval operator+(const Interval &) const;
    Interval operator-(const Interval &) const;
    Interval operator*(const Interval &)const;
    Interval operator/(const Interval &) const;

    tribool operator<(const Interval &) const;
    tribool operator>(const Interval &) const;
    tribool operator==(const Interval &) const;
    tribool operator<=(const Interval &) const;
    tribool operator>=(const Interval &) const;

    Interval operator+(INT);
    Interval operator-(INT);
    Interval operator*(INT);
    Interval operator/(INT);

    Interval operator-() const;
    Interval operator&(const Interval &)const;
    Interval operator|(const Interval &) const;

    static inline std::pair<INT, INT> get_limits();
    static inline INT max_value();
    static inline INT min_value();
    static inline std::pair<INT, INT> top_limits();
    inline INT length() const;

    bool isTop();
    bool isBot();
    std::pair<INT, INT> getInterval();
};

} // namespace intervalai

#endif
