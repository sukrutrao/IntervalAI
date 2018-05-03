#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <string>
#include <vector>

namespace intervalai {

class ArgParser {
  private:
    std::vector<std::string> args;

  public:
    ArgParser(int, char **);
    bool argExists(std::string);
    std::string getArgValue(std::string);
};

} // namespace intervalai

#endif