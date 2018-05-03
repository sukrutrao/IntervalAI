#include "arg_parser.h"
#include "display_utils.h"
#include <iostream>

int main_(int argc, char *argv[]) {
    intervalai::ArgParser arg_parser(argc, argv);
    if (arg_parser.argExists("-h") || argc < 2) {
        intervalai::displayHelp(argv[0]);
    }
    return 0;
}