#ifndef EXPR_HANDLER_H
#define EXPR_HANDLER_H

#include <functional>
#include <map>
#include <util/expr.h>
#include <util/irep.h>

#include "interval_domain.h"

namespace intervalai {

class ExprHandler {

  public:
    static std::map<irep_idt, Interval> symbol_table;
    static std::map<irep_idt, std::function<Interval(exprt)>> function_map;
    static std::map<irep_idt, std::function<Interval(Interval &, Interval &)>>
        arithmetic_ops;

    static Interval get_identifier(exprt);
    static bool is_identifier(exprt);
    static Interval get_constant(exprt);
    static bool is_constant(exprt);
    static Interval get_interval(exprt);

  // public:
    ExprHandler();

    static Interval handleExpr(exprt);

    static Interval handleArithmeticExpr(exprt);
};

}; // namespace intervalai

#endif