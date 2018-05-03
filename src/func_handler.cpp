#include "func_handler.h"
#include "instruction_handler.h"
#include <iostream>

using namespace intervalai;

FuncHandler::FuncHandler (goto_modelt *m) {
	assert(m != nullptr);
	model = m;
}

bool FuncHandler::handleInstruction(std::_List_iterator<instructiont> current) {
	std::cout << (*current).to_string() << std::endl;
    auto instruction = *current;
    if (instruction.is_end_function()) {
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
    bool safe = instruction_handler.handleInstruction(*current);
    if (!safe) {
    	return false;
    }
	return handleInstruction(++current);
}

std::pair<bool, Interval> FuncHandler::handleFunc(std::string func_name) {
	auto instructions = model->goto_functions.function_map["main"].body.instructions;
    intervalai::InstructionHandler instruction_handler;
    handleInstruction(instructions.begin());
}
