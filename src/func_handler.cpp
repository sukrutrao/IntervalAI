#include "func_handler.h"
#include "instruction_handler.h"
#include <iostream>

using namespace intervalai;

FuncHandler::FuncHandler(goto_modelt *m) {
    assert(m != nullptr);
    model = m;
}

bool FuncHandler::handleInstruction(std::_List_iterator<instructiont> current) {
    std::cout << (*current).to_string() << std::endl;
    auto instruction = *current;
    if (instruction.is_return()) {
    	instruction_handler.handleInstruction(instruction);
    	// set func_return TODO
    	return true;
    }
    if (instruction.is_end_function()) {
        return true;
    }
    if (instruction.is_function_call()) {
    	auto operands = instruction_handler.handleFunctionCall(instruction);
    	// TODO pass arguments to functions
    	auto params = model->goto_functions.function_map[id2string(std::get<1>(operands))].parameter_identifiers;
    	for (auto &param : params) {
    		std::cout << param << std::endl;
    	}
    	auto return_val = handleFunc(id2string(std::get<1>(operands)));
    	if (!return_val.first) {
    		return false;
    	}
    	if (id2string(std::get<0>(operands)) != "") {
    		instruction_handler.expr_handler.symbol_table[id2string(std::get<0>(operands))] = return_val.second;
    	}
    	return true;
    }
    if (instruction.is_goto()) {
        intervalai::tribool guard = instruction_handler.handleGoto(*current);
        if (guard == intervalai::tribool::True) {
            return handleInstruction(instruction.targets.front());
        } else if (guard == intervalai::tribool::False) {
            return handleInstruction(++current);
        } else {
            bool branch1 = handleInstruction(instruction.targets.front());
            if (branch1) {
                return handleInstruction(++current);
            } else {
                return false;
            }
        }
    }
    bool safe = instruction_handler.handleInstruction(instruction);
    if (!safe) {
        return false;
    }
    return handleInstruction(++current);
}

std::pair<bool, Interval> FuncHandler::handleFunc(std::string func_name) {
    auto instructions =
        model->goto_functions.function_map["main"].body.instructions;
    intervalai::InstructionHandler instruction_handler;
    bool is_safe = handleInstruction(instructions.begin());
    return std::make_pair(is_safe, func_return);
}
