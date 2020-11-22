#ifndef OKC_ASSIGN_STATE_H
#define OKC_ASSIGN_STATE_H

#include "finite_state.h"

// Abstract base class for Finite State Automata classes
class State
{
  public:
    virtual EState next_state(char c) = 0;
    virtual ~State() {} // To get around spurious warning
};

class StartState : public State
{
  private:
    EState next_state(char c) override;
};

class AlphaState: public State
{
  private:
     EState next_state(char c) override;
};

class OpenBraceState : public State
{
  private:
     EState next_state(char c) override;
};

class CloseBraceState : public State 
{
  private:
     EState next_state(char c) override;
};

class CommaState : public State
{
  private:
     EState next_state(char c) override;
};

#endif // OKC_ASSIGN_STATE_H