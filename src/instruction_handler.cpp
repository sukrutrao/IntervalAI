#include "instruction_handler.h"
#include <iostream>

using namespace intervalai;

InstructionHandler::InstructionHandler() {}

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
    } else if (instruction.is_return()) {
        handleReturn(instruction);
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
        std::cout << "HANDLE THIS" << std::endl;
    }
    return true;
}

tribool InstructionHandler::handleGoto(instructiont instruction) {
    std::cout << instruction.guard.pretty() << std::endl;
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

void InstructionHandler::handleReturn(instructiont instruction) {}

void InstructionHandler::handleAssume(instructiont instruction) {}

tribool InstructionHandler::handleAssert(instructiont instruction) {
    auto assert = instruction.guard;
    // std::cout << assert.pretty() << std::endl;
    auto guard_val = expr_handler.handleBooleanExpr(assert);
    if (guard_val != tribool::True) {
        std::cout << "BUG" << std::endl;
    }
    return guard_val;
    // std::cout << assert.operands().size() << std::endl;
}

void InstructionHandler::handleSkip(instructiont instruction) {}

void InstructionHandler::handleFunctionCall(instructiont instruction) {}

void InstructionHandler::handleOther(instructiont instruction) {}