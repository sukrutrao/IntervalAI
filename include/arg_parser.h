#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include "func_handler.h"
#include <string>
#include <vector>

namespace intervalai {

class ArgParser {
  private:
    std::vector<std::string> args;

  public:
    ArgParser(int, char **);
    bool argExists(std::string);
    RunMode getArgValue(std::string);
};

} // namespace intervalai

#endif