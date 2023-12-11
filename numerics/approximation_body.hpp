#pragma once

#include "geometry/barycentre_calculator.hpp"
#include "numerics/approximation.hpp"
#include "numerics/fixed_arrays.hpp"
#include "quantities/elementary_functions.hpp"
#include "quantities/numbers.hpp"

namespace principia {
namespace numerics {
namespace _approximation {
namespace internal {

using namespace principia::geometry::_barycentre_calculator;
using namespace principia::numerics::_fixed_arrays;
using namespace principia::quantities::_elementary_functions;
using namespace principia::quantities::_si;

template<typename Argument, typename Function, int N>
ЧебышёвSeries<Value<Function, Argument>>
ЧебышёвPolynomialInterpolantImplementation(
    Function const& f,
    Argument const& a,
    Argument const& b,
    Difference<Value<Function, Argument>> const& max_error,
    FixedVector<Value<Function, Argument>, N / 2 + 1> const& previous_fₖ,
    FixedVector<Value<Function, Argument>, N / 2 + 1> const& previous_aⱼ) {
  auto const midpoint = Barycentre({a, b}, {0.5, 0.5});

  auto чебышёв_lobato_point = [&a, &b](std::int64_t const k) -> Argument {
    return 0.5 * (b - a) * Cos(π * k * Radian / N) + midpoint;
  };

  FixedVector<Value<Function, Argument>, N + 1>& fₖ;
  FixedVector<Value<Function, Argument>, N + 1>& a;

  // Reuse the previous evaluations of |f|.
  for (std::int64_t k = 0; k <= N / 2; ++k) {
    fₖ[2 * k] = previous_fₖ[k];
  }

  // Evaluate |f| for the new points.
  for (std::int64_t k = 1; k < N; k += 2) {
    fₖ[k] = f(чебышёв_lobato_point(k, N));
  }

  FixedMatrix<double, N + 1, N + 1> ℐⱼₖ;
  for (std::int64_t j = 0; j <= N; ++j) {
    double const pⱼ = j == 0 || j == N ? 2 : 1;
    for (std::int64_t k = 0; k <= N; ++k) {
      double const pₖ = k == 0 || k == N ? 2 : 1;
      ℐⱼₖ(j, k) = 2 * Cos(π * j * k * Radian / N) / (pⱼ * pₖ * N);
    }
  }

  // Compute the coefficients of the Чебышёв polynomial.
  auto const aⱼ = ℐⱼₖ * fₖ;

  // Compute an upper bound for the error, based on the previous and new
  // polynomials.
  Difference<Value<Function, Argument>> error_estimate;
  for (std::int64_t j = 0; j <= N / 2; ++j) {
    error_estimate += Abs(previous_aⱼ[j] - aⱼ[j]);
  }
  for (std::int64_t j = N / 2 + 1; j <= N; ++j) {
    error_estimate += previous_aⱼ[j];
  }

  if (error_estimate < max_error) {
    return ЧебышёвSeries(aⱼ, a, b);
  } else {
    return ЧебышёвPolynomialInterpolantImplementation(
        f, a, b, max_error, fₖ, aⱼ);
  }
}

template<typename Argument, typename Function>
ЧебышёвSeries<Value<Function, Argument>> ЧебышёвPolynomialInterpolant(
    Function const& f,
    Argument const& lower_bound,
    Argument const& upper_bound,
    Difference<Value<Function, Argument>> const& max_error) {
  auto const& a = lower_bound;
  auto const& b = upper_bound;
  auto const f_a = f(a);
  auto const f_b = f(b);
  FixedVector<Value<Function, Argument>, 2> const fₖ({f_b, f_a});
  FixedVector<Value<Function, Argument>, 2> const aⱼ(
      {0.5 * (f_b + f_a), 0.5 * (f_b - f_a)});
  return ЧебышёвPolynomialInterpolantImplementation<Argument,
                                                    Function,
                                                    /*N=*/2>(
      f, a, b, max_error, fₖ, aⱼ);
}

}  // namespace internal
}  // namespace _approximation
}  // namespace numerics
}  // namespace principia
