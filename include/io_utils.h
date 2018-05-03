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
void displayResult(bool);
void displayTitle();

enum class RunMode { Interactive, Automated, Error };

} // namespace intervalai

#endif