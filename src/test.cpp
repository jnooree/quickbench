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
    ret.emplace_back(Eigen::Matrix3d::Random().colwise().normalized());
  return ret;
}();

void use_acos(benchmark::State &state) {
  for (auto _ : state) {
    for (const auto &m : ms) {
      double average = COS_VALUES(m).array().min(1).max(-1).acos().mean();
      benchmark::DoNotOptimize(average < 0.238942);
    }
  }
}

BENCHMARK_ALWAYS_INLINE inline auto tan2_common(const Eigen::Matrix3d &m) {
  Eigen::Array3d cosines = COS_VALUES(m),
                 sines = (1 - cosines.square().min(1)).sqrt();
  return std::make_pair(sines.sum(), cosines.sum());
}

void use_atan2(benchmark::State &state) {
  for (auto _ : state) {
    for (const auto &m : ms) {
      auto [ssum, csum] = tan2_common(m);
      benchmark::DoNotOptimize(std::atan2(ssum, csum) < 0.238942);
    }
  }
}

void use_tan2(benchmark::State &state) {
  for (auto _ : state) {
    for (const auto &m : ms) {
      auto [ssum, csum] = tan2_common(m);
      benchmark::DoNotOptimize(csum * -0.238942 < ssum);
    }
  }
}

BENCHMARK(use_acos);
BENCHMARK(use_atan2);
BENCHMARK(use_tan2);
} // namespace
