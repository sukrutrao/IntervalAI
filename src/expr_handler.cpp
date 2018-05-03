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
    Interval op_intervals[2], result;
    for (auto i = 0; i < 2; i++) {
        auto op = expr.operands()[i];
        if (op.has_operands()) {
            op_intervals[i] = handleExpr(op);
        } else {
            op_intervals[i] = get_interval(op);
        }
    }
    result = arithmetic_ops.at(expr.id())(op_intervals[0], op_intervals[1]);
    return result;
}

Interval ExprHandler::get_interval(exprt expr) {
    auto expr_map = expr.get_named_sub();
    if (expr_map.find("identifier") != expr_map.end()) {
        return symbol_table.at(expr_map["identifier"].id());
    } else if (expr_map.find("value") != expr_map.end()) {
        INT constant_value =
            std::stoi(expr_map["value"].id_string(), nullptr, 2);
        return Interval(constant_value, constant_value);
    } else {
        assert(false); // TODO: remove this
    }
    return Interval(true);
}