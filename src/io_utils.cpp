#include "io_utils.h"
#include <fstream>

using namespace intervalai;

void intervalai::displayUnknownMode() {
    std::cout << "Unrecognized Abstract Interpreter mode" << std::endl;
    std::cout << "Available modes : interactive, automated" << std::endl;
}

void intervalai::displayHelp(std::string name) {
    std::cout << "Usage : " << name << " [-v] [-h] [-m <mode>] <goto-binary>"
              << std::endl;
}

void intervalai::displayAbout() {
    std::cout << "Interval Domain Abstract Interpreter on Integer Domains"
              << std::endl;
}

bool intervalai::fileExists(std::string name) {
    std::ifstream gotofile(name.c_str());
    return gotofile.good();
}

void intervalai::displayUnknownFile(std::string name) {
    std::cout << "Could not open file : " << name << std::endl;
}