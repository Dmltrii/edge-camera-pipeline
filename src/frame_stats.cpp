#include "frame_stats.h"

#include <algorithm>  // minmax_element
#include <cmath>
#include <numeric>  // accumulate
#include <optional>
#include <unordered_map>

namespace {
double compute_stddev(const std::vector<int>& frame, double mean) {
  double sum_sq{};
  for (int v : frame) {
    sum_sq += (v - mean) * (v - mean);
  }
  return std::sqrt(sum_sq / static_cast<double>(frame.size()));
}

int compute_mode(const std::vector<int>& frame) {
  std::unordered_map<int, int> counts;
  for (int num : frame) {
    counts[num]++;
  }
  int max_count{};
  int max_value{};
  for (const auto& pair : counts) {
    if (pair.second > max_count) {
      max_count = pair.second;
      max_value = pair.first;
    } else if (pair.second == max_count) {
      if (pair.first < max_value) {
        max_value = pair.first;
      }
    }
  }
  return max_value;
}
}  // namespace

std::optional<FrameStats> compute_stats(const std::vector<int>& frame) {
  if (frame.empty()) return std::nullopt;
  auto [min, max] = std::minmax_element(frame.begin(), frame.end());
  long long sum{std::accumulate(frame.begin(), frame.end(), 0LL)};

  double mean = static_cast<double>(sum) / frame.size();
  double stddev{compute_stddev(frame, mean)};
  int mode{compute_mode(frame)};
  return FrameStats{*min, *max, mean, stddev, mode};
}
