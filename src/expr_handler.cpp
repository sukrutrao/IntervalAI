#include "expr_handler.h"

#include <cassert>
#include <util/std_expr.h>

using namespace intervalai;

std::map<irep_idt, Interval> ExprHandler::symbol_table;
std::map<irep_idt, std::function<Interval(exprt)>> ExprHandler::function_map;
std::map<irep_idt, std::function<Interval(Interval &, Interval &)>>
    ExprHandler::arithmetic_ops;

ExprHandler::ExprHandler() {
    function_map.emplace(ID_plus, handleArithmeticExpr);
    function_map.emplace(ID_minus, handleArithmeticExpr);
    function_map.emplace(ID_mult, handleArithmeticExpr);
    function_map.emplace(ID_div, handleArithmeticExpr);
    arithmetic_ops.emplace(ID_plus, std::plus<Interval>());
    arithmetic_ops.emplace(ID_minus, std::minus<Interval>());
    arithmetic_ops.emplace(ID_mult, std::multiplies<Interval>());
    //    arithmetic_ops.emplace(ID_div, std::divides<Interval>());
}

Interval ExprHandler::handleExpr(exprt expr) {
    return function_map.at(expr.id())(expr);
}

Interval ExprHandler::handleArithmeticExpr(exprt expr) {
    assert(expr.id() == ID_plus || expr.id() == ID_minus ||
           expr.id() == ID_mult || expr.id() == ID_div);
    assert(expr.operands().size() == 2);
    auto op1 = expr.operands()[0];
    auto op2 = expr.operands()[1];
    Interval result;
    if (op1.has_operands()) {
        result = handleExpr(op1);
    } else {
        result = get_interval(op1);
    }
    Interval interval_op2 = get_interval(op2);
    result = arithmetic_ops.at(expr.id())(result, interval_op2);
    return result;
}

// check if this can be simplified
bool ExprHandler::is_identifier(exprt expr) {
    for (auto i = expr.get_named_sub().begin(); i != expr.get_named_sub().end();
         i++) {
        if (i->first == "identifier") {
            return true;
        }
    }
    return false;
}

// check if this can be simplified
bool ExprHandler::is_constant(exprt expr) {
    for (auto i = expr.get_named_sub().begin(); i != expr.get_named_sub().end();
         i++) {
        if (i->first == "value") {
            return true;
        }
    }
    return false;
}

Interval ExprHandler::get_identifier(exprt expr) {
    Interval result;
    irep_idt symbol_name;
    for (auto i = expr.get_named_sub().begin(); i != expr.get_named_sub().end();
         i++) {
        if (i->first == "identifier") {
            symbol_name = i->second.id();
        }
    }
    return symbol_table.at(symbol_name);
}

Interval ExprHandler::get_constant(exprt expr) {
    Interval result;
    return result;
}

Interval ExprHandler::get_interval(exprt expr) {
    if (is_identifier(expr)) {
        return get_identifier(expr);
    } else if (is_constant(expr)) {
        return get_constant(expr);
    }
}