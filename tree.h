#ifndef OKC_ASSIGN_TREE_H
#define OKC_ASSIGN_TREE_H

#include "finite_state.h"
#include <memory>
#include <string>
#include <vector>
#include <exception>

class Node
{
  public:
    explicit Node(Node* n = nullptr) : parent_(n) {}
    void add_label(char c);
    std::string get_label() const;
    Node* add_child();
    Node* add_sibling();
    Node* get_parent() const;
    void generate(std::vector<std::string>& tokens);
    void dump() const;
  
  private:
    std::string label_;
    std::vector<std::unique_ptr<Node>> children_;
    std::unique_ptr<Node> sibling_;
    Node* parent_;
};

class Tree
{
  public:
      void update_tree(EState state, char c);
      std::vector<std::string> generate() const;
      bool is_valid() const;
  private:
    std::unique_ptr<Node> root_node_ = std::make_unique<Node>();
    Node* curr_node_ = root_node_.get();
};

#endif