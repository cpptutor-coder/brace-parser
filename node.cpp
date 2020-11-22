#include "node.h"
#include <iostream>
#include <list>

using namespace std;
namespace
{
    vector<string> combine(vector<string> vec1, vector<string> vec2)
    {
        vector<string> tokens;
        for (auto &v1 : vec1)
        {
            for (auto &v2 : vec2)
            {
                tokens.push_back(v1 + v2);
            }
        }
        return tokens;
    }

    void dump_vector(vector<string> vec)
    {
        for (auto &v : vec)
        {
            cout << v << " ";
        }
        cout << endl;
    }

} // namespace

void Node::add_label(char c)
{
    label_.push_back(c);
}

string Node::get_label() const
{
    return label_;
}

Node* Node::add_child()
{
    children_.push_back(make_unique<Node>(this));
    return children_.back().get();
}

Node* Node::add_sibling()
{
    sibling_ = make_unique<Node>(get_parent());
    return sibling_.get();
}

Node* Node::get_parent() const
{
    return parent_;
}

void Node::generate(vector<string> &tokens)
{
    //dump();
    if (children_.size() > 0)
    {
        list<vector<string>> child_tokens;
        for (auto &v : children_)
        {
            vector<string> memo;
            v->generate(memo);
            assert(memo.size() > 0);
            //dump_vector(memo);
            child_tokens.push_back(memo);
        }
        assert(child_tokens.size() > 0);
        vector<string> combined = child_tokens.front();
        child_tokens.pop_front();
        for (auto &v : combined)
        {
            v = label_ + v;
        }
        while (!child_tokens.empty())
        {
            //dump_vector(combined);
            combined = combine(combined, child_tokens.front());
            child_tokens.pop_front();
        }

        copy(combined.begin(), combined.end(), back_inserter(tokens));
    }
    else
    {
        assert(!label_.empty());
        tokens.push_back(label_);
    }

    if (sibling_ != nullptr)
    {
        sibling_->generate(tokens);
    }
}

void Node::dump() const
{
    cout << (void *)this << " " << label_;
    for (auto &v : children_)
    {
        cout << " Child: " << (void *)v.get() << " " << v->get_label();
    }
    cout << " Sibling: " << (void *)sibling_.get() << " " << (sibling_ ? sibling_->get_label() : "");
    auto sp = parent_;
    cout << " Parent: " << (void *)sp << " " << (sp ? sp->get_label() : "")
         << endl;
}