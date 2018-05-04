#include "expr_handler.h"

#include <cassert>
#include <iostream>
#include <util/std_expr.h>

using namespace intervalai;

std::map<irep_idt, Interval> ExprHandler::symbol_table;
std::map<irep_idt, std::function<Interval(Interval &, Interval &)>>
    ExprHandler::arithmetic_ops;

ExprHandler::ExprHandler() {

    arithmetic_ops.emplace(ID_plus, std::plus<Interval>());
    arithmetic_ops.emplace(ID_minus, std::minus<Interval>());
    arithmetic_ops.emplace(ID_mult, std::multiplies<Interval>());
    arithmetic_ops.emplace(ID_div, std::divides<Interval>());
}

tribool ExprHandler::handleBooleanExpr(exprt expr) {
    assert(expr.id() == ID_lt || expr.id() == ID_gt || expr.id() == ID_le ||
           expr.id() == ID_ge || expr.id() == ID_equal ||
           expr.id() == ID_notequal || expr.id() == ID_and ||
           expr.id() == ID_or || expr.id() == ID_not);
    if (expr.id() == ID_lt || expr.id() == ID_gt || expr.id() == ID_le ||
        expr.id() == ID_ge || expr.id() == ID_equal ||
        expr.id() == ID_notequal) {
        return handleRelationalExpr(expr);
    }
    return handleLogicalExpr(expr);
}

tribool ExprHandler::handleLogicalExpr(exprt expr) {
    assert(expr.id() == ID_and || expr.id() == ID_or || expr.id() == ID_not);
    assert(expr.operands().size() <= 2);
    tribool op_bool[2], result;
    for (auto i = 0; i < 2; i++) {
        if (expr.operands().size() == i) {
            break;
        }
        auto op = expr.operands()[i];
        op_bool[i] = handleBooleanExpr(op);
    }
    if (expr.id() == ID_and) {
        result = op_bool[0] && op_bool[1];
    } else if (expr.id() == ID_or) {
        result = op_bool[0] || op_bool[1];
    } else if (expr.id() == ID_not) {
        result = !(op_bool[0]);
    }
    return result;
}

tribool ExprHandler::handleRelationalExpr(exprt expr) {
    assert(expr.id() == ID_lt || expr.id() == ID_gt || expr.id() == ID_le ||
           expr.id() == ID_ge || expr.id() == ID_equal ||
           expr.id() == ID_notequal);
    assert(expr.operands().size() == 2);
    Interval op_bool[2];
    tribool result;
    for (auto i = 0; i < 2; i++) {
        auto op = expr.operands()[i];
        if (op.has_operands()) {
            op_bool[i] = handleArithmeticExpr(op);
        } else {
            op_bool[i] = get_interval(op);
        }
    }
    if (expr.id() == ID_lt) {
        result = op_bool[0] < op_bool[1];
    } else if (expr.id() == ID_gt) {
        result = op_bool[0] > op_bool[1];
    } else if (expr.id() == ID_le) {
        result = op_bool[0] <= op_bool[1];
    } else if (expr.id() == ID_ge) {
        result = op_bool[0] >= op_bool[1];
    } else if (expr.id() == ID_equal) {
        result = op_bool[0] == op_bool[1];
    } else if (expr.id() == ID_notequal) {
        result = op_bool[0] != op_bool[1];
    }
    return result;
}

Interval ExprHandler::handleArithmeticExpr(exprt expr) {
    if (!expr.has_operands()) {
        return get_interval(expr);
    }
    if (expr.id() == ID_unary_plus || expr.id() == ID_unary_minus) {
        assert(expr.operands().size() == 1);
        if (expr.id() == ID_unary_plus) {
            return handleArithmeticExpr(expr.operands()[0]);
        }
        return -handleArithmeticExpr(expr.operands()[0]);
    }
    assert(expr.id() == ID_plus || expr.id() == ID_minus ||
           expr.id() == ID_mult || expr.id() == ID_div);
    assert(expr.operands().size() == 2);
    Interval op_intervals[2], result;
    for (auto i = 0; i < 2; i++) {
        auto op = expr.operands()[i];
        if (op.has_operands()) {
            op_intervals[i] = handleArithmeticExpr(op);
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
        assert(false);
    }
    return Interval(true);
}