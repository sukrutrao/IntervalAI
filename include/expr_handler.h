#ifndef EXPR_HANDLER_H
#define EXPR_HANDLER_H

#include <functional>
#include <map>
#include <util/expr.h>
#include <util/irep.h>

#include "interval_domain.h"

namespace intervalai {

class ExprHandler {

  private:
    // static std::map<irep_idt, std::function<Interval(exprt)>> function_map;
    static std::map<irep_idt, std::function<Interval(Interval &, Interval &)>>
        arithmetic_ops;
    // static std::map<irep_idt, std::function<tribool(Interval &, Interval &)>>
    //     relational_ops;
    // static std::map<irep_idt, std::function<tribool(tribool, tribool)>>
    //     logical_ops;


  public:
    ExprHandler();
    static Interval get_interval(exprt);
    static std::map<irep_idt, Interval> symbol_table;
    // static Interval handleExpr(exprt);
    static tribool handleBooleanExpr(exprt);
    static tribool handleRelationalExpr(exprt);
    static Interval handleArithmeticExpr(exprt);
    static tribool handleLogicalExpr(exprt);
};

}; // namespace intervalai

#endif