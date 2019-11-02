#pragma once

#include <array>
#include <algorithm>
#include <cassert>
#include <type_traits>


namespace data_structures {

template<typename T>
using is_arithmetic = std::enable_if_t<std::is_arithmetic_v<T>>;

template<typename M1, typename M2>
using can_be_multiplied = std::enable_if_t<
  std::is_same_v<M1::T, M2::T> &&
  M1::rows_ == M2::cols_ &&
  M1::cols_ == M2::rows_>;

template <typename T, std::size_t rows_, std::size_t cols_,
          typename = is_arithmetic<T>>
struct matrix {
  using reference = T&;
  using const_reference = T const&;
  constexpr reference operator()(std::size_t row, std::size_t col) noexcept {
    return storage[index(row, col)];
  }
  constexpr const_reference operator()(std::size_t row, std::size_t col) const noexcept {
    return storage[index(row, col)];
  }

  constexpr std::size_t rows() const noexcept {
    return rows_;
  }

  constexpr std::size_t cols() const noexcept {
    return cols_;
  }

  friend constexpr matrix<T, rows_, rows_> operator*(
      matrix const& lhs, matrix<T, cols_, rows_> const& rhs) {
    matrix<T, rows_, rows_> result;
    for (auto i = 0u; i < rows_; ++i) {
      for (auto j = 0u; j < rows_; ++j) {
        T element = 0;
        for (auto k = 0u; k < cols_; ++k) {
          element += lhs(i, k) * rhs(k, j);
        }
        result(i, j) = element;
      }
    }
    return result;
  }

  matrix& operator*=(T value) noexcept {
    std::transform(begin(storage), end(storage), begin(storage),
        [value](auto a){ return a * value; });
    return *this;
  }

  friend matrix operator*(matrix lhs, T rhs) noexcept {
    lhs *= rhs;
    return lhs;
  }

  friend matrix operator*(T lhs, matrix rhs) noexcept {
    rhs *= lhs;
    return rhs;
  }

  matrix& operator+=(matrix const & other) noexcept {
    assert(other.rows() == rows() && other.cols() == cols());

    std::transform(begin(storage), end(storage),
        begin(other.storage), begin(storage), std::plus<>());

    return *this;
  }

  friend matrix operator+(matrix lhs, matrix const & rhs) noexcept {
    lhs += rhs;
    return lhs;
  }

  std::array<T, rows_ * cols_> storage;

private:
  constexpr std::size_t index(std::size_t row, std::size_t col) const noexcept {
    return cols_ * row + col;
  }
};

template<typename T, std::size_t l_rows, std::size_t l_cols,
                     std::size_t r_rows, std::size_t r_cols,
         typename = is_arithmetic<T>>
constexpr inline bool operator==(matrix<T, l_rows, l_cols> const &lhs,
                       matrix<T, r_rows, r_cols> const &rhs) noexcept {
  return l_rows == r_rows && l_cols == r_cols && lhs.storage == rhs.storage;
}

template<typename T, std::size_t l_rows, std::size_t l_cols,
                     std::size_t r_rows, std::size_t r_cols,
         typename = is_arithmetic<T>>
constexpr inline bool operator!=(matrix<T, l_rows, l_cols> const &lhs,
                       matrix<T, r_rows, r_cols> const &rhs) noexcept {
  return !(lhs == rhs);
}
}
