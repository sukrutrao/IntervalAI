#include <iostream>
#include <string>
#include "interval_domain.h"
#include <goto-programs/read_goto_binary.h>
#include <goto-programs/goto_model.h>
#include <util/cout_message.h>
#include <util/std_code.h>

int main(int argc, char **argv) {

	goto_modelt model;
	cout_message_handlert message_handler;

	bool error = read_goto_binary(std::string(argv[1]), model, message_handler);

	if (error) {
		return 1;
	}

	auto instructions = model.goto_functions.function_map["main"].body.instructions;

	auto symbols = model.symbol_table.symbols;

	for (auto s : symbols) {
		symbolt sym = s.second;
		if (sym.is_procedure_local()) {
			std::cout << sym.display_name() << " " << sym.is_file_local << " " << sym.type.id_string() << std::endl;
		}
		// std::cout << 100 << s.first << std::endl;
	}

	for (auto instruction : instructions) {
		if (instruction.is_assign()) {
			auto assign = static_cast<code_assignt &>(instruction.code);
			auto rhs = assign.rhs();
			if (rhs.id() == ID_plus) {
				std::cout << to_plus_expr(rhs).op0().pretty() << std::endl;
			}
			
		}
	}

	return 0;
}
