#ifndef FUNC_HANDLER_H
#define FUNC_HANDLER_H

#include "instruction_handler.h"
#include "interval_domain.h"
#include "io_utils.h"
#include <goto-programs/goto_model.h>
#include <string>

namespace intervalai {

class FuncHandler {
  public:
    FuncHandler(goto_modelt *model, RunMode mode = RunMode::Automated);
    std::pair<bool, Interval> handleFunc(std::string func_name);

  private:
    goto_modelt *model;
    Interval func_return;
    RunMode mode;
    InstructionHandler instruction_handler;
    bool handleInstruction(std::_List_iterator<instructiont> current);
    void displayInfo(std::_List_iterator<instructiont> current);
    std::string prompt;
};

}; // namespace intervalai

#endif