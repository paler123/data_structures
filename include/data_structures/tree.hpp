#pragma once

#include <set>
#include <queue>

namespace data_structures {

namespace detail {
template <typename T>
struct compare {
  bool operator()(T* lhs, T* rhs) const {
    if (lhs && rhs)
      return lhs->val < rhs->val;
    return false;
  }
};
}

template <typename T, typename S>
using IsSimilar = std::enable_if_t<std::is_same_v<std::decay_t<S>, std::decay_t<T>>>;

template <typename T>
class SortedTree {
  struct Node {
    template<typename S,
      typename = IsSimilar<S, T>>
    bool add_child(S&& val) {
      return children.emplace(new Node(std::forward<S>(val)), {}).second;
    }
    bool is_leaf() {
      return children.empty();
    }
    T val;
    using Children = std::set<Node*, detail::compare<Node>>;
    Children children;
  };
 public:
  SortedTree() = default;
  SortedTree(SortedTree&&) = default;
  SortedTree& operator=(SortedTree&&) = default;
  SortedTree(SortedTree const& other) {
    std::queue<Node*> other_queue;
    std::queue<Node*> this_queue;
    if(other.root) {
      this->root = new Node(other.root.val);
      other_queue.push(other.root);
      this_queue.push(this->root);
    }
    while (!other_queue.empty()) {
      auto other_node = other_queue.front();
      auto this_node = this_queue.front();
      for (auto child : other_node->children) {
        this_node->add_child(child->val);
        other_queue.push(child);
      }
      for (auto child : this_node->children) {
        this_queue.push(child);
      }
    }
  }
  SortedTree& operator=(SortedTree const& other) {
    SortedTree tmp(other);
    std::swap(tmp, *this);
    return *this;
  }
  Node* get_root() { return root; }
  Node const* get_root() const { return root; }
  enum class ReturnPolicy {
    Early,
    Default
  };
  template <typename Visitor>
  void visit (Visitor&& visitor) const {
    auto queue = std::queue<Node*>{};
    if (root)
      queue.push(root);
    while (!queue.empty()) {
      auto current_node = queue.front();
      for (auto child : current_node->children)
        queue.push(child);
      ReturnPolicy visit_result = visitor(current_node);
      if (visit_result == ReturnPolicy::Early)
        return;
      queue.pop();
    }
  }

  template <typename Visitor>
  void visit (Visitor&& visitor) {
    std::as_const(*this).
        visit(std::forward<Visitor>(visitor));
  }

  ~SortedTree() {
    visit([](Node* node){
     delete node;
     return ReturnPolicy::Default;
    });
  }
 private:
  Node* root;

};

}
