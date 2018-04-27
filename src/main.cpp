#include <iostream>
#include <string>
#include "interval_domain.h"
#include <goto-programs/read_goto_binary.h>
#include <goto-programs/goto_model.h>
#include <util/cout_message.h>

int main(int argc, char **argv) {

	goto_modelt model;
	cout_message_handlert message_handler;

	bool error = read_goto_binary(std::string(argv[1]), model, message_handler);

	if (error) {
		return 1;
	}

	auto instructions = model.goto_functions.function_map["main"].body.instructions;

	for (auto instruction: instructions) {
		std::cout << instruction.to_string() << std::endl;
	}

	return 0;
}
