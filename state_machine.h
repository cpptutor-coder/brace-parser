
#ifndef OKC_ASSIGN_STATE_MACHINE_H
#define OKC_ASSIGN_STATE_MACHINE_H

#include "tree.h"
#include "finite_state.h"
#include <string>
#include <vector>
#include <map>

class State;
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

#endif // OKC_ASSIGN_STATE_MACHINE_H
