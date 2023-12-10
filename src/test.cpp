#include <Eigen/Dense>
#include <benchmark/benchmark.h>
#include <cmath>
#include <vector>

#define COS_VALUES(m) m.cwiseProduct(m(Eigen::all, {1, 2, 0})).colwise().sum()

namespace {
const auto ms = []() {
  std::vector<Eigen::Matrix3d> ret;
  ret.reserve(100);
  for (int i = 0; i < 100; ++i)
    ret.emplace_back(Eigen::Matrix3d::Random().eval().colwise().normalized());
  return ret;
}();

constexpr double kAlpha = 2.007;
constexpr double kHalfAlpha = kAlpha / 2;
const double kTanHalfAlpha = std::tan(kHalfAlpha);

void use_acos(benchmark::State &state) {
  int n = 0;
  for (const auto &m : ms) {
    double average = COS_VALUES(m).array().min(1).max(-1).acos().mean();
    n += average <= kAlpha;
  }
  state.counters["n"] = n;

  for (auto _ : state) {
    for (const auto &m : ms) {
      double average = COS_VALUES(m).array().min(1).max(-1).acos().mean();
      benchmark::DoNotOptimize(average <= kAlpha);
    }
  }
}

BENCHMARK_ALWAYS_INLINE inline auto half_tan2_common(const Eigen::Matrix3d &m) {
  double csum = (m + m(Eigen::all, {1, 2, 0})).colwise().norm().sum(),
         ssum = (m - m(Eigen::all, {1, 2, 0})).colwise().norm().sum();
  return std::make_pair(ssum, csum);
}

void use_atan2(benchmark::State &state) {
  int n = 0;
  for (const auto &m : ms) {
    auto [ss, cs] = half_tan2_common(m);
    n += std::atan2(ss, cs) <= kHalfAlpha;
  }
  state.counters["n"] = n;

  for (auto _ : state) {
    for (const auto &m : ms) {
      auto [ss, cs] = half_tan2_common(m);
      benchmark::DoNotOptimize(std::atan2(ss, cs) <= kHalfAlpha);
    }
  }
}

void use_tan2(benchmark::State &state) {
  int n = 0;
  for (const auto &m : ms) {
    auto [ss, cs] = half_tan2_common(m);
    n += ss <= cs * kTanHalfAlpha;
  }
  state.counters["n"] = n;

  for (auto _ : state) {
    for (const auto &m : ms) {
      auto [ss, cs] = half_tan2_common(m);
      benchmark::DoNotOptimize(ss <= cs * kTanHalfAlpha);
    }
  }
}

BENCHMARK(use_acos);
BENCHMARK(use_atan2);
BENCHMARK(use_tan2);
} // namespace
