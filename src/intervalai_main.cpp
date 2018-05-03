#include "arg_parser.h"
#include "func_handler.h"
#include "io_utils.h"
#include <iostream>

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
    }
    return 0;
}