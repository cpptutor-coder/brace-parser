#include "state_machine.h"
#include "state.h"
#include <iostream>

using namespace std;

StateMachine::StateMachine(std::string const &input) : input_data_(input)
{
    state_lookup.emplace(make_pair(EState::start, make_unique<StartState>()));
    state_lookup.emplace(make_pair(EState::alpha, make_unique<AlphaState>()));
    state_lookup.emplace(make_pair(EState::open_brace, make_unique<OpenBraceState>()));
    state_lookup.emplace(make_pair(EState::close_brace, make_unique<CloseBraceState>()));
    state_lookup.emplace(make_pair(EState::comma, make_unique<CommaState>()));
}

// Required for unique_ptr member variable
StateMachine::~StateMachine() = default;

// Validates the given data and builds the tree
bool StateMachine::build()
{
    bool valid = true;
    auto curr_state = state_lookup[EState::start].get();
    for (auto c : input_data_)
    {
        auto state = curr_state->next_state(c);
        if (state != EState::invalid)
        {
            auto it = state_lookup.find(state);
            assert(it != state_lookup.end());
            curr_state = it->second.get();
            try
            {
                tree_.build_tree(state, c);
            }
            catch(const std::exception& e)
            {
                valid = false;
                break;
            }
        }
        else
        {
            valid = false;
            break;
        }
    }

    return valid && tree_.is_valid();
}

vector<string> StateMachine::generate() const
{
    return tree_.generate();
}