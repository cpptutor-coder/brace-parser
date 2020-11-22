#ifndef OKC_ASSIGN_NODE_H
#define OKC_ASSIGN_NODE_H

#include <string>
#include <vector>
#include <memory>

class Node
{
  public:
    explicit Node(Node* n) : parent_(n) {}
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

#endif // OKC_ASSIGN_NODE_H