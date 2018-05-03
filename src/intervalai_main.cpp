#include "arg_parser.h"
#include "func_handler.h"
#include "io_utils.h"
#include <goto-programs/goto_model.h>
#include <goto-programs/read_goto_binary.h>
#include <iostream>
#include <string>
#include <util/cout_message.h>
#include <util/std_code.h>

int main(int argc, char *argv[]) {
    intervalai::ArgParser arg_parser(argc, argv);
    if (arg_parser.argExists("-h") || argc < 2) {
        intervalai::displayHelp(argv[0]);
        return 0;
    }
    if (arg_parser.argExists("-v")) {
        intervalai::displayAbout();
        return 0;
    }
    intervalai::displayTitle();
    intervalai::RunMode mode = intervalai::RunMode::Automated;
    if (arg_parser.argExists("-m")) {
        mode = arg_parser.getArgValue("-m");
        if (mode == intervalai::RunMode::Error) {
            intervalai::displayUnknownMode();
        }
    }
    std::string goto_binary_name = std::string(argv[argc - 1]);
    if (!intervalai::fileExists(goto_binary_name)) {
        intervalai::displayUnknownFile(goto_binary_name);
        return 1;
    }

    goto_modelt model;
    cout_message_handlert message_handler;

    bool error = read_goto_binary(goto_binary_name, model, message_handler);

    if (error) {
        std::cout << "err" << std::endl;
        return 1;
    }

    unsigned widen_limit = 100;

    intervalai::FuncHandler func_handler(&model, widen_limit, mode);

    auto result = func_handler.handleFunc("main");

    intervalai::displayResult(result.first);

    return 0;
}