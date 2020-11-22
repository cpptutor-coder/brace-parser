#ifndef OKC_ASSIGN_TREE_H
#define OKC_ASSIGN_TREE_H

#include "finite_state.h"
#include "node.h"
#include <memory>
#include <string>
#include <vector>

class Tree
{
  public:
      void build_tree(EState state, char c);
      std::vector<std::string> generate() const;
      bool is_valid() const;
  private:
    std::unique_ptr<Node> root_node_ = std::make_unique<Node>(nullptr);
    Node* curr_node_ = root_node_.get();
};

#endif