#pragma once

#include <string>
#include <unordered_map>
#include <memory>


template <typename String>
struct Trie {
  using CharT = typename String::value_type;
  bool insert(String const& value) {
    return insert_impl(value);
  }
  bool has_value(String const& value) {
    return has_value_impl(value);
  }
  bool any_substring_found(String const& value) {
    return any_substring_found_impl(value);
  }
 private:
  struct Node {
    std::unordered_map<CharT, std::unique_ptr<Node>> children;
  };
  std::unique_ptr<Node> root = std::make_unique<Node>();

  bool insert_impl(String const& value) {
    bool inserted = false;
    auto value_it = std::cbegin(value);
    auto node = root.get();
    while (value_it != std::cend(value) && !inserted) {
      auto insert_result = node->children.emplace(*value_it, std::make_unique<Node>());
      if (insert_result.second)
        inserted = true;
      node = insert_result.first->second.get();
      ++value_it;
    }
    if (inserted) {
      while (value_it != std::cend(value)) {
        auto insert_result = node->children.emplace(*value_it, std::make_unique<Node>());
        node = insert_result.first->second.get();
        ++value_it;
      }
    }
    return inserted;
  }


  bool has_value_impl(String const& value) {
    auto node = root.get();
    for (auto c : value) {
      auto c_it = node->children.find(c);
      if (c_it == std::cend(node->children))
        return false;
      node = c_it->second.get();
    }
    return node->children.empty();
  }
};

