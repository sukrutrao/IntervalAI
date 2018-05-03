#include "expr_handler.h"
#include "interval_domain.h"
#include <goto-programs/goto_model.h>
#include <goto-programs/read_goto_binary.h>
#include <iostream>
#include <string>
#include <util/cout_message.h>
#include <util/std_code.h>

#include "expr_handler.h"

int main(int argc, char **argv) {

    goto_modelt model;
    cout_message_handlert message_handler;

    bool error = read_goto_binary(std::string(argv[1]), model, message_handler);

    if (error) {
    	std::cout << "err" << std::endl;
        return 1;
    }

    auto instructions = model.goto_functions.function_map["main"].body.instructions;

    intervalai::ExprHandler expr_handler;

    auto symbols = model.symbol_table.symbols;

    for (auto &sym : symbols) {
    	expr_handler.symbol_table[sym.first] = intervalai::Interval();
    }

    auto current = instructions.begin();

    std::cout << "Here" << std::endl;

    while (current != instructions.end()) {
    	if ((*current).is_end_function()) {
    		break;
    	} else if ((*current).is_assign()) {
    		auto assign = static_cast<code_assignt&>((*current).code);
    		auto interval = expr_handler.handleExpr(assign.rhs());
    		std::cout << assign.lhs().get_named_sub()["identifier"].id() << std::endl;
    	} else if ((*current).is_dead()) {
    		// Remove from symbol table
    	} else if ((*current).is_decl()) {
    		// Add to symbol table
    	}

    	std::cout << (*current).code.get_statement() << std::endl;
    	if ((*current).is_goto()) {
    		std::cout << "GOTO";
    		std::cout << (*current).targets.size();
    		std::cout << (*(*current).targets.front()).type << std::endl;
    		// auto inst = static_cast<goto_exprt>(*current);
    		// auto code = (*current).code;
    		// std::cout << code.get_statement() << std::endl;
    		// auto goto_code = to_code_goto(code);
    		// std::cout << goto_code.get_destination() << std::endl;
    		current = (*(current)).targets.front();
    		continue;
    	}
    	current++;
    }

    for (auto &i: instructions) {
    	std::cout << i.type << std::endl;
    }

    // for (auto s : symbols) {
    //     symbolt sym = s.second;
    //     if (sym.is_procedure_local()) {
    //         std::cout << sym.display_name() << " " << sym.is_file_local << " "
    //                   << sym.type.id_string() << std::endl;
    //     }
    //     // std::cout << 100 << s.first << std::endl;
    // }

    // for (auto instruction : instructions) {
    //     std::cout << instruction.to_string() << std::endl;
    //     if (instruction.is_assign()) {
    //         auto assign = static_cast<code_assignt &>(instruction.code);
    //         auto rhs = assign.rhs();
    //         if (rhs.id() == ID_plus) {
    //             //	std::cout << to_plus_expr(rhs).op0().pretty() << std::endl;
    //             auto p = rhs;
    //             std::cout << "RHS ID: " << rhs.id() << std::endl;
    //             for (auto op = p.operands().begin(); op != p.operands().end();
    //                  op++) {
    //                 std::cout << "Op: " << (*op).id() << (*op).has_operands()
    //                           << std::endl;
    //                 for (auto i = op->get_named_sub().begin();
    //                      i != op->get_named_sub().end(); i++) {
    //                     std::cout << "First: " << (*i).first << std::endl;
    //                     std::cout << "Second: " << (*i).second.id()
    //                               << std::endl;
    //                 }
    //                 //    std::cout << (*op).get_named_sub(). << std::endl;
    //             }
    //         }
    //     }
    // }

    return 0;
}
