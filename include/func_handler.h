#ifndef FUNC_HANDLER_H
#define FUNC_HANDLER_H

#include "interval_domain.h"
#include "instruction_handler.h"
#include <string>
#include <goto-programs/goto_model.h>

namespace intervalai {
	class FuncHandler {
	public:
		FuncHandler(goto_modelt *model);
		std::pair<bool, Interval> handleFunc(std::string func_name);
	private:
		goto_modelt *model;
		InstructionHandler instruction_handler;
		bool handleInstruction(std::_List_iterator<instructiont> current);
	};
};

#endif