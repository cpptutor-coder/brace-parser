
// parse the input
// make sure it's valid
// then build the data structure
// Generate once built
#include "state.h"
#include <list>
#include <iostream> // VIK_TODO: Remove later on

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


EState next_state(char c, shared_ptr<Node>& node, string const& valid_tokens)
{
    // throw exception if node is null
    if (node == nullptr) {
        cout << "ERROR: Encountered null pointer" << endl;
        throw(runtime_error(""));
    }

    if (valid_tokens.find(c) == string::npos) {
        //cout << "VIK_DEBUG: Invalid token: " << c << endl;
        return EState::invalid;
    }

    if (isalpha(c)) {
        node->add_data(c);
        return EState::alpha;
    }
    else if (isopen_brace(c)) {
        node = node->add_child();
        return EState::open_brace;
    }
    else if (iscomma(c)) {
        node = node->add_sibling();
        return EState::comma;
    }
    else if (isclose_brace(c)) {
        // Go to parent but make sure the node has child if it's empty
        node = node->get_parent();
        return (node == nullptr? EState::invalid : EState::close_brace);
    }

    return EState::invalid;

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



    EState StartState::next_state(char c, shared_ptr<Node>& node)
    {
        return ::next_state(c, node, "{abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }

     EState AlphaState::next_state(char c, shared_ptr<Node>& node)
     {
        return ::next_state(c, node, "{,}abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
     }

     EState OpenBraceState::next_state(char c, shared_ptr<Node>& node)
     {
         return ::next_state(c, node, "{abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
     }

    // VIK_TODO: Error if returning empty to parent and don't have any child
     EState CloseBraceState::next_state(char c, shared_ptr<Node>& node)
     {
         // VIK_TODO: Find out if alpha can come too
         return ::next_state(c, node, "{}");
     }

    // VIK_TODO: Error if created at root level
     EState CommaState::next_state(char c, shared_ptr<Node>& node)
     {
        return ::next_state(c, node, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
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
        auto curr_node = root_node_;
        auto curr_state = state_lookup[EState::start];
        curr_node->dump();
        for(auto c: input) {
            try {
                auto state = curr_state->next_state(c, curr_node);
            }
            catch{std::logic_error& e} {
                valid = false;
                break;
            }
            
            if (state != EState::invalid) {
                curr_node->dump();
                auto it = state_lookup.find(state);
                assert(it != state_lookup.end());
                curr_state = it->second;
            }
            else {
                valid = false;
                break;
            }
        }


        bool braces_matched = (curr_node == root_node_);
        return valid && braces_matched;
    }

    vector<string> StateMachine::generate() const
    {
        vector<string> tokens;
        root_node_->generate(tokens);
        return tokens;
    }