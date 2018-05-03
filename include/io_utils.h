#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <iostream>
#include <string>

namespace intervalai {

void displayHelp(std::string);
void displayAbout();
void displayUnknownMode();
bool fileExists(std::string);
void displayUnknownFile(std::string);

} // namespace intervalai

#endif