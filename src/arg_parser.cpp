#include "arg_parser.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

using namespace intervalai;

ArgParser::ArgParser(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }
}

bool ArgParser::argExists(std::string check_arg) {
    if (std::find(args.begin(), args.end(), check_arg) != args.end()) {
        return true;
    }
    return false;
}

RunMode ArgParser::getModeValue(std::string get_arg) {
    if (std::find(args.begin(), args.end(), get_arg) == args.end()) {
        return RunMode::Error;
    }
    auto it = std::find(args.begin(), args.end(), get_arg);
    it++;
    if (it != args.end()) {
        if (*it == "auto") {
            return RunMode::Automated;
        } else if (*it == "step") {
            return RunMode::Interactive;
        }
    }
    return RunMode::Error;
}

unsigned ArgParser::getIntValue(std::string get_arg) {
    if (std::find(args.begin(), args.end(), get_arg) == args.end()) {
        return -1;
    }
    auto it = std::find(args.begin(), args.end(), get_arg);
    it++;
    int result = -1;
    if (it != args.end()) {
        std::istringstream ss(*it);

        ss >> result;
        return result;
    }
    return result;
}