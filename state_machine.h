
#ifndef OKC_ASSIGN_STATE_MACHINE_H
#define OKC_ASSIGN_STATE_MACHINE_H

#include "tree.h"
#include "finite_state.h"
#include <string>
#include <vector>
#include <map>

class State;
// Class used to accept the brace tokens and generate the output
class StateMachine
{
  public:
    StateMachine(std::string const& input);
    ~StateMachine();
    bool build();
    std::vector<std::string> generate() const;
  private:
    std::string input_data_;
    Tree tree_;
    std::map<EState, std::unique_ptr<State>> state_lookup;
};

#endif // OKC_ASSIGN_STATE_MACHINE_H
