#include "expr_handler.h"
#include "instruction_handler.h"
#include "interval_domain.h"
#include <goto-programs/goto_model.h>
#include <goto-programs/read_goto_binary.h>
#include <iostream>
#include <string>
#include <util/cout_message.h>
#include <util/std_code.h>
#include "func_handler.h"

#include "expr_handler.h"

int main(int argc, char **argv) {

    // intervalai::Interval a(intervalai::Interval::min_value(), -1),
    //     b(-10, intervalai::Interval::max_value());
    // a.view();
    // b.view();
    // auto c = a * b;
    // c.view();

    goto_modelt model;
    cout_message_handlert message_handler;

    bool error = read_goto_binary(std::string(argv[1]), model, message_handler);

    if (error) {
    	std::cout << "err" << std::endl;
        return 1;
    }

    intervalai::FuncHandler func_handler(&model);
    func_handler.handleFunc("main");

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
