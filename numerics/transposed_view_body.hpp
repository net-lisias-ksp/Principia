#pragma once

#include "numerics/transposed_view.hpp"

namespace principia {
namespace numerics {
namespace _transposed_view {
namespace internal {

template<typename T>
int TransposedView<T>::rows() const
  requires two_dimensional<T> && unbounded<T> {
  // Note the transposition.
  return transpose.columns();
}

template<typename T>
int TransposedView<T>::columns() const
  requires two_dimensional<T> && unbounded<T> {
  // Note the transposition.
  return transpose.rows();
}

template<typename T>
int TransposedView<T>::size() const
  requires one_dimensional<T> && unbounded<T> {
  return transpose.size();
}

template<typename T>
constexpr typename T::Scalar& TransposedView<T>::operator[](int index)
  requires one_dimensional<T> {
  return transpose[index];
}

template<typename T>
constexpr typename T::Scalar const& TransposedView<T>::operator[](
    int index) const
  requires one_dimensional<T> {
  return transpose[index];
}

template<typename T>
constexpr typename T::Scalar& TransposedView<T>::operator()(int row, int column)
  requires two_dimensional<T> {
  // Note the transposition.
  return transpose(column, row);
}

template<typename T>
constexpr typename T::Scalar const& TransposedView<T>::operator()(
    int row,
    int column) const
  requires two_dimensional<T> {
  // Note the transposition.
  return transpose(column, row);
}

}  // namespace internal
}  // namespace _transposed_view
}  // namespace numerics
}  // namespace principia
