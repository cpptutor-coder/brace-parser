#include "state_machine.h"
#include "state.h"
#include <iostream>

using namespace std;

StateMachine::StateMachine()
{
    state_lookup.emplace(make_pair(EState::start, make_shared<StartState>()));
    state_lookup.emplace(make_pair(EState::alpha, make_shared<AlphaState>()));
    state_lookup.emplace(make_pair(EState::open_brace, make_shared<OpenBraceState>()));
    state_lookup.emplace(make_pair(EState::close_brace, make_shared<CloseBraceState>()));
    state_lookup.emplace(make_pair(EState::comma, make_shared<CommaState>()));
}

bool StateMachine::build(std::string const &input)
{
    bool valid = true;
    auto curr_state = state_lookup[EState::start];
    for (auto c : input)
    {
        auto state = curr_state->next_state(c);
        if (state != EState::invalid)
        {
            auto it = state_lookup.find(state);
            assert(it != state_lookup.end());
            curr_state = it->second;
            try
            {
                tree_.update_tree(state, c);

            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
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