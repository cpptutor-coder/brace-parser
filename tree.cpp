#include "tree.h"
#include <iostream>
#include <list>

using namespace std;
namespace
{
    vector<string> combine(vector<string> vec1, vector<string> vec2)
    {
        vector<string> tokens;
        for(auto& v1 : vec1) {
            for(auto& v2: vec2) {
                tokens.push_back(v1+v2);
            }
        }
        return tokens;
    }

    void dump_vector(vector<string> vec)
    {
        for(auto& v: vec) {
            cout << v << " ";
        }
        cout << endl;
    }

} // namespace

void Node::add_data(char c)
    {
        data_.push_back(c);
    }

    string Node::get_data() const
    {
        return data_;
    }
    
    shared_ptr<Node> Node::add_child()
    {
        auto child = make_shared<Node>();
        child->set_parent(shared_from_this());
        children_.push_back(child);
        return children_.back();
    }

    shared_ptr<Node> Node::add_sibling()
    {
        sibling_ = make_shared<Node>();
        sibling_->set_parent(get_parent());
        return sibling_;
    }

    shared_ptr<Node> Node::get_parent() const
    {
       return parent_.lock();
    }

void Node::generate(vector<string>& tokens)
    {
        cout << "VIK_DEBUG: generate" << endl;
        dump();
        if (children_.size() > 0) {
            list<vector<string>> child_tokens;
            for(auto& v: children_) {
                vector<string> memo;
                v->generate(memo);
                assert(memo.size() > 0);
                dump_vector(memo);
                child_tokens.push_back(memo);
            }
            assert(child_tokens.size() > 0);
            vector<string> combined = child_tokens.front();
            child_tokens.pop_front();
            for(auto& v: combined) {
                v = data_ + v;
            }
            while(!child_tokens.empty()) {
                dump_vector(combined);
                combined = combine(combined, child_tokens.front());
                child_tokens.pop_front();
            }
            
            copy(combined.begin(), combined.end(), back_inserter(tokens));
        }
        else {
            assert(!data_.empty());
            tokens.push_back(data_);
        }

        if (sibling_ != nullptr) {
            sibling_->generate(tokens);
        }
    }

    void Node::dump() const
    {
        cout << (void*)this << " " << data_;
        for (auto& v: children_) {
            cout << " Child: " << (void*)v.get() << " " << v->get_data(); 
        }
        cout << " Sibling: " << (void*)sibling_.get() << " " << (sibling_ ? sibling_->get_data() : "");
        auto sp = parent_.lock();
        cout << " Parent: " << (void*)sp.get() << " " << (sp ? sp->get_data() : "")
        << endl;
    }

    void Node::set_parent(weak_ptr<Node> p)
    {
        parent_ = p;
    }

void Tree::update_tree(EState state, char c)
{
    assert(state != EState::invalid);

    switch(state) {
        case EState::start:
        case EState::alpha:
            curr_node_->add_data(c);
        break;
        case EState::open_brace:
            curr_node_ = curr_node_->add_child();
        break;
        case EState::close_brace:
            curr_node_ = curr_node_->get_parent();
            if (curr_node_ == nullptr) {
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
    return (curr_node_ == root_node_);
}