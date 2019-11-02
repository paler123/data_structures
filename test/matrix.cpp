#include "matrix.hpp"

#include "catch2/catch.hpp"

namespace {
using namespace data_structures;

TEST_CASE("MatrixArithmetic", "[matrix]") {
  matrix<int, 2u, 2u> zero2x2 {0, 0, 0, 0};
  matrix<int, 2u, 2u> n1 {1, 3, 3, 4};
  matrix<int, 4u, 4u> m2 {1,  2,  3,  4,
                          5,  6,  7,  8,
                          9,  10, 11, 12,
                          13, 14, 15, 16};
  matrix<int, 4u, 4u> n2 {16, 15, 14, 13,
                          12, 11, 10, 9,
                          8,  7,  6,  5,
                          4,  3,  2,  1};
  SECTION("Addition 2x2") {
    zero2x2 += n1;
    REQUIRE( zero2x2(0, 0) == 1);
    REQUIRE( zero2x2(0, 1) == 3);
    REQUIRE( zero2x2(1, 0) == 3);
    REQUIRE( zero2x2(1, 1) == 4);
    REQUIRE( zero2x2 == n1);
  }
  SECTION("Addittion 4x4") {
    auto sum = m2 + n2;
    for (auto i = 0u; i < 4u; ++i) {
      for (auto j = 0u; j < 4u; ++j) {
        REQUIRE( sum(i, j) == 17 );
      }
    }
  }
  SECTION("Scalar multiplication by 0") {
    n1 *= 0;
    REQUIRE( n1 == zero2x2 );
  }
  SECTION("Scalar multiplication is comutative") {
    auto multiplied1 = n2 * 3;
    auto multiplied2 = 3 * n2;
    REQUIRE(multiplied1 == multiplied2);
    REQUIRE(multiplied1(0, 0) == 48);
  }
  SECTION("Matrix multiplication square matrices") {
    auto prod1 = n1 * zero2x2;
    REQUIRE(prod1 == zero2x2);

    auto identity2x2 = matrix<int, 2, 2>{1, 0, 0, 1};
    auto prod2 = n1 * identity2x2;
    REQUIRE(prod2 == n1);
  }
}

}
