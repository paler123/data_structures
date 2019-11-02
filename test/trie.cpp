#include "trie.hpp"

#include <catch2/catch.hpp>

namespace
{

TEST_CASE("Trie", "[trie testing]")
{
  Trie<std::string> test_trie;
  test_trie.insert("kupa");
  REQUIRE(test_trie.has_value("kupa"));
  REQUIRE(!test_trie.has_value("ku"));
  REQUIRE(!test_trie.has_value("kurczak"));
  test_trie.insert("kurczak");
  REQUIRE(test_trie.has_value("kurczak"));
  REQUIRE(test_trie.has_value("kupa"));
}

}

