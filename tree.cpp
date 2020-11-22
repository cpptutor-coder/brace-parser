#include "tree.h"
#include <iostream>

using namespace std;

void Tree::update_tree(EState state, char c)
{
    assert(state != EState::invalid);
    switch (state)
    {
    case EState::start:
    case EState::alpha:
        curr_node_->add_label(c);
        break;
    case EState::open_brace:
        curr_node_ = curr_node_->add_child();
        break;
    case EState::close_brace:
        curr_node_ = curr_node_->get_parent();
        if (curr_node_ == nullptr)
        {
            throw runtime_error("Parsing error. One or more extra \"}\" ");
        }
        break;
    case EState::comma:
        curr_node_ = curr_node_->add_sibling();
        break;
    default:
        assert(false);
        throw logic_error("Unknown EState");
    }
}

vector<string> Tree::generate() const
{
    vector<string> tokens;
    root_node_->generate(tokens);
    return tokens;
}

bool Tree::is_valid() const
{
    return (curr_node_ == root_node_.get());
}