#include "display_utils.h"

using namespace intervalai;

void intervalai::displayUnknownMode(std::string mode) {
    std::cout << "Unrecognized Abstract Interpreter mode : " << mode
              << std::endl;
}

void intervalai::displayHelp(std::string name) {
    std::cout << "Usage : " << name << "[-v] [-h] [-m <mode>] <goto-binary>"
              << std::endl;
}