#include "instruction_handler.h"
#include <iostream>

using namespace intervalai;

InstructionHandler::InstructionHandler(RunMode mode) { this->mode = mode; }

bool InstructionHandler::handleInstruction(instructiont instruction) {
    if (instruction.is_assign()) {
        handleAssign(instruction);
    } else if (instruction.is_dead()) {
        handleDead(instruction);
    } else if (instruction.is_decl()) {
        handleDecl(instruction);
    } else if (instruction.is_assume()) {
        handleAssume(instruction);
    } else if (instruction.is_skip()) {
        handleSkip(instruction);
    } else if (instruction.is_function_call()) {
        handleFunctionCall(instruction);
    } else if (instruction.is_other()) {
        handleOther(instruction);
    } else if (instruction.is_assert()) {
        auto assert_val = handleAssert(instruction);
        if (assert_val != intervalai::tribool::True) {
            return false;
        }
    } else if (instruction.is_assume()) {
        handleAssume(instruction);
    } else {
        std::cout << "Unknown instruction type encountered" << std::endl;
        return false;
    }
    return true;
}

tribool InstructionHandler::handleGoto(instructiont instruction) {
    // std::cout << instruction.guard.pretty() << std::endl;
    if (instruction.guard.is_true()) {
        return tribool::True;
    }
    return expr_handler.handleBooleanExpr(instruction.guard);
}

void InstructionHandler::handleDecl(instructiont instruction) {
    auto decl = static_cast<code_declt &>(instruction.code);
    expr_handler
        .symbol_table[decl.symbol().get_named_sub()["identifier"].id()] =
        intervalai::Interval();
}

void InstructionHandler::handleDead(instructiont instruction) {
    auto dead = static_cast<code_deadt &>(instruction.code);
    expr_handler.symbol_table.erase(
        dead.symbol().get_named_sub()["identifier"].id());
}

void InstructionHandler::handleAssign(instructiont instruction) {
    auto assign = static_cast<code_assignt &>(instruction.code);
    auto interval = expr_handler.handleArithmeticExpr(assign.rhs());
    // std::cout << "RHS parsed" << std::endl;
    expr_handler.symbol_table[assign.lhs().get_named_sub()["identifier"].id()] =
        interval;
}

Interval InstructionHandler::handleReturn(instructiont instruction) {
    auto return_i = static_cast<code_returnt &>(instruction.code);
    // std::cout << return_i.return_value().pretty() << std::endl;
    auto ret = expr_handler.handleArithmeticExpr(return_i.return_value());
    // std::cout << "RET" << ret.to_string() << std::endl;
    return ret;
}

void InstructionHandler::handleAssume(instructiont instruction) { return; }

tribool InstructionHandler::handleAssert(instructiont instruction) {
    auto assert = instruction.guard;
    // std::cout << assert.pretty() << std::endl;
    auto guard_val = expr_handler.handleBooleanExpr(assert);
    if (guard_val != tribool::True) {
        std::cout << "Assertion Failed. Instruction : "
                  << instruction.location_number << ", "
                  << instruction.to_string() << std::endl;
    } else {
        if (mode == RunMode::Interactive) {
            std::cout << "Assertion Passed. Instruction : "
                      << instruction.location_number << ", "
                      << instruction.to_string() << std::endl;
        }
    }
    return guard_val;
    // std::cout << assert.operands().size() << std::endl;
}

void InstructionHandler::handleSkip(instructiont instruction) {}

std::tuple<dstringt, dstringt, std::vector<Interval>>
InstructionHandler::handleFunctionCall(instructiont instruction) {
    auto func_call = static_cast<code_function_callt &>(instruction.code);
    auto lhs = func_call.lhs().get_named_sub()["identifier"].id();
    auto func = func_call.function().get_named_sub()["identifier"].id();
    std::vector<Interval> intervals;
    for (auto &op : func_call.arguments()) {
        // std::cout << op.pretty() << std::endl;
        if (op.has_operands()) {
            intervals.push_back(expr_handler.handleArithmeticExpr(op));
        } else {
            intervals.push_back(expr_handler.get_interval(op));
        }
    }
    return std::make_tuple(lhs, func, intervals);
}

void InstructionHandler::handleOther(instructiont instruction) {}