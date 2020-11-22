#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>
#include <string>
#include <map>

enum class EState {
    start,
    alpha,
    open_brace,
    close_brace,
    comma,
    invalid
};

class Node : public std::enable_shared_from_this<Node>
{
  public:
  // VIK_TODO: Find out how to set the parent from constructor itself
    //explicit Node(Node* n = nullptr) : parent_(n) {}
    void add_data(char c); // VIK_TODO: See if we can send in constructor
    std::string get_data() const; // VIK_TODO: Maybe change name to something better or at least get_label
    std::shared_ptr<Node> add_child();
    std::shared_ptr<Node> add_sibling();
    std::shared_ptr<Node> get_parent() const;
    void generate(std::vector<std::string>& tokens);
    void dump() const;
  private:
  // VIK_TODO: Find how not to need it and set in constructor itself
    void set_parent(std::weak_ptr<Node> p);

    std::string data_;
    // VIK_TODO: Make them unique_ptr again later on
    std::vector<std::shared_ptr<Node>> children_;
    std::shared_ptr<Node> sibling_;
    std::weak_ptr<Node> parent_;
};

class State
{
  public:
    virtual EState next_state(char c, std::shared_ptr<Node>& node) = 0;
};

class StartState : public State
{
  private:
    EState next_state(char c, std::shared_ptr<Node>& node) override;
};

class AlphaState: public State
{
  private:
     EState next_state(char c, std::shared_ptr<Node>& node) override;
};

class OpenBraceState : public State
{
  private:
     EState next_state(char c, std::shared_ptr<Node>& node) override;
};

class CloseBraceState : public State 
{
  private:
     EState next_state(char c, std::shared_ptr<Node>& node) override;
};

class CommaState : public State
{
  private:
     EState next_state(char c, std::shared_ptr<Node>& node) override;
};

class StateMachine
{
  public:
    StateMachine();
    bool build(std::string const& input);
    std::vector<std::string> generate() const;
  private:
    std::shared_ptr<Node> root_node_ = std::make_shared<Node>();
    std::map<EState, std::shared_ptr<State>> state_lookup;
};

#endif // STATE_H