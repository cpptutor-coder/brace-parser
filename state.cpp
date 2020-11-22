
// parse the input
// make sure it's valid
// then build the data structure
// Generate once built
#include "state.h"
#include "tree.h"
#include <list>
#include <iostream> // VIK_TODO: Remove later on

using namespace std;

namespace 
{
    
    bool iscomma(char c)
{
    return (c == ',');
}

bool isopen_brace(char c)
{
    return (c == '{');
}

bool isclose_brace(char c)
{
    return (c == '}');
}

EState next_state(char c, string const &valid_tokens)
{
    if (valid_tokens.find(c) == string::npos)
    {
        return EState::invalid;
    }

    if (isalpha(c))
    {
        return EState::alpha;
    }
    else if (isopen_brace(c))
    {
        return EState::open_brace;
    }
    else if (iscomma(c))
    {
        return EState::comma;
    }
    else if (isclose_brace(c))
    {
        // VIK_TODO: Make sure brace count >= 0
        return EState::close_brace;
    }

    return EState::invalid;
}

} // namespace


    EState StartState::next_state(char c)
    {
        auto state = EState::invalid;
        if (isalpha(c)) {
            state = EState::start;
        }
        else if (isopen_brace(c)) {
            state = EState::open_brace;
        }
       
        return state;
    }

     EState AlphaState::next_state(char c)
     {
        auto state = EState::invalid;
        if (isalpha(c)) {
            state = EState::alpha;
        }
        else if (isopen_brace(c)) {
            state = EState::open_brace;
        }
        else if (isclose_brace(c)) {
            state = EState::close_brace;
        }
        else if (iscomma(c)) {
            state =  EState::comma;
        }

        return state;
     }

     EState OpenBraceState::next_state(char c)
     {
        auto state = EState::invalid;
        if (isalpha(c)) {
            state = EState::alpha;
        }
        else if (isopen_brace(c)) {
            state = EState::open_brace;
        }

        return state;
     }

    // VIK_TODO: Error if returning empty to parent and don't have any child
     EState CloseBraceState::next_state(char c)
     {
        auto state = EState::invalid;
        if (isopen_brace(c)) {
            state = EState::open_brace;
        }
        else if (isclose_brace(c)) {
            // Keep a count of  braces and return
            // invalid if the count becomes negative
            state = EState::close_brace;
        }

        return state;
     }

     EState CommaState::next_state(char c)
     {
        auto state = EState::invalid;
        if (isalpha(c)) {
            state = EState::alpha;
        }
        return state;
     }

    StateMachine::StateMachine()
    {
        state_lookup.emplace(make_pair(EState::start, make_shared<StartState>()));
        state_lookup.emplace(make_pair(EState::alpha, make_shared<AlphaState>()));
        state_lookup.emplace(make_pair(EState::open_brace, make_shared<OpenBraceState>()));
        state_lookup.emplace(make_pair(EState::close_brace, make_shared<CloseBraceState>()));
        state_lookup.emplace(make_pair(EState::comma, make_shared<CommaState>()));
    }

    bool StateMachine::build(std::string const& input)
    {
        bool valid = true;
        auto curr_state = state_lookup[EState::start];
        for(auto c: input) {
            auto state = curr_state->next_state(c);
            if (state != EState::invalid) {
                auto it = state_lookup.find(state);
                assert(it != state_lookup.end());
                curr_state = it->second;
                tree_.update_tree(state, c);
            }
            else {
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