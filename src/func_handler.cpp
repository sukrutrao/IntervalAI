#include "func_handler.h"
#include "instruction_handler.h"
#include <iostream>

using namespace intervalai;

FuncHandler::FuncHandler (goto_modelt *m, RunMode mode) : mode(mode) {
    assert(m != nullptr);
    model = m;
}

bool FuncHandler::handleInstruction(std::_List_iterator<instructiont> current) {
    while (mode == RunMode::Interactive) {
        std::string str;
        std::cout << "cbmc>> ";
        std::cin >> str;
        if (str == "n") {
            break;
        } else if (str == "p") {
            for (auto &sym : instruction_handler.expr_handler.symbol_table) {
                std::cout << sym.first << "\t" << sym.second.to_string() << std::endl;
            }
        } else {
            std::cout << "invalid commnad" << std::endl;
        }
    }
    std::cout << (*current).to_string() << std::endl;
    auto instruction = *current;
    if (instruction.is_return()) {
    	Interval interval = instruction_handler.handleReturn(instruction);
        func_return = interval;
        std::cout << func_return.to_string() << std::endl;
    	return true;
    }
    if (instruction.is_end_function()) {
        return true;
    }
    if (instruction.is_function_call()) {
    	auto operands = instruction_handler.handleFunctionCall(instruction);
        auto params = model->goto_functions.function_map[std::get<1>(operands)].type.parameters();
        auto argument_it = std::get<2>(operands).begin();

        for (auto &param : params) {
            instruction_handler.expr_handler.symbol_table[param.get_identifier()] = *argument_it;
            argument_it++;
        }

    	auto return_val = handleFunc(id2string(std::get<1>(operands)));
    	if (!return_val.first) {
    		return false;
    	}
    	if (id2string(std::get<0>(operands)) != "") {
    		instruction_handler.expr_handler.symbol_table[id2string(std::get<0>(operands))] = return_val.second;
    	}
    }
    if (instruction.is_goto()) {
        intervalai::tribool guard = instruction_handler.handleGoto(*current);
        if (guard == intervalai::tribool::True) {
            return handleInstruction(instruction.targets.front());
        } else if (guard == intervalai::tribool::False) {
            return handleInstruction(++current);
        } else {
            if (mode == RunMode::Interactive) {
                std::cout << "Whicg branch?>> ";
                std::string str;
                std::cin >> str;
                if (str == "1") {
                    return handleInstruction(instruction.targets.front());
                } else {
                    return handleInstruction(++current);
                }
            } else {
                bool branch1 = handleInstruction(instruction.targets.front());
                if (branch1) {
                    return handleInstruction(++current);
                } else {
                    return false;
                }
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
        model->goto_functions.function_map[func_name].body.instructions;
    intervalai::InstructionHandler instruction_handler;
    auto params = model->goto_functions.function_map[func_name].type.parameters();
    for (auto &param : params) {
        std::cout << instruction_handler.expr_handler.symbol_table[param.get_identifier()].to_string() << std::endl;
    }
    bool is_safe = handleInstruction(instructions.begin());
    return std::make_pair(is_safe, func_return);
}
