
#include "state.h"
#include "tree.h"
#include <list>

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

} // namespace

EState StartState::next_state(char c)
{
    auto state = EState::invalid;
    if (isalpha(c))
    {
        state = EState::start;
    }
    else if (isopen_brace(c))
    {
        state = EState::open_brace;
    }

    return state;
}

EState AlphaState::next_state(char c)
{
    auto state = EState::invalid;
    if (isalpha(c))
    {
        state = EState::alpha;
    }
    else if (isopen_brace(c))
    {
        state = EState::open_brace;
    }
    else if (isclose_brace(c))
    {
        state = EState::close_brace;
    }
    else if (iscomma(c))
    {
        state = EState::comma;
    }

    return state;
}

EState OpenBraceState::next_state(char c)
{
    auto state = EState::invalid;
    if (isalpha(c))
    {
        state = EState::alpha;
    }
    else if (isopen_brace(c))
    {
        state = EState::open_brace;
    }

    return state;
}

EState CloseBraceState::next_state(char c)
{
    auto state = EState::invalid;
    if (isopen_brace(c))
    {
        state = EState::open_brace;
    }
    else if (isclose_brace(c))
    {
        state = EState::close_brace;
    }

    return state;
}

EState CommaState::next_state(char c)
{
    auto state = EState::invalid;
    if (isalpha(c))
    {
        state = EState::alpha;
    }
    return state;
}