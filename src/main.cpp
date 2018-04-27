#include <iostream>
#include "interval_domain.h"
#include <goto-programs/read_goto_binary.h>
#include <goto-programs/goto_model.h>
#include <util/cout_message.h>

int main() {

	goto_modelt model;
	cout_message_handlert message_handler;

	bool error = read_goto_binary("../../cbmctests/e.goto", model, message_handler);

	if (error) {
		std::cerr << "Error!" << std::endl;
	} else {
		model.output(std::cout);
	}

	return 0;
}
