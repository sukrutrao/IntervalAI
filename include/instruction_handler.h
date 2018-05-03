#ifndef INSTRUCTION_HANDLER_H
#define INSTRUCTION_HANDLER_H

#include "expr_handler.h"
#include "interval_domain.h"
#include <goto_program.h>

namespace intervalai {

class InstructionHandler {

  private:
    ExprHandler expr_handler;

  public:
    InstructionHandler();
    void handleInstruction(instructiont);

    void handleAssign(insturctiont);
    void handleDead(insturctiont);
    void handleDecl(insturctiont);
    void handleGoto(insturctiont);
};

}; // namespace intervalai

#endif