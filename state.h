#ifndef OKC_ASSIGN_STATE_H
#define OKC_ASSIGN_STATE_H

#include "finite_state.h"
#include "tree.h"
#include <memory>
#include <vector>
#include <string>
#include <map>

class State
{
  public:
    virtual EState next_state(char c) = 0;
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

class StateMachine
{
  public:
    StateMachine();
    bool build(std::string const& input);
    std::vector<std::string> generate() const;
  private:
    Tree tree_;
    std::map<EState, std::shared_ptr<State>> state_lookup;
};

#endif // STATE_H