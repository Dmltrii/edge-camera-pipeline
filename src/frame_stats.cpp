#include "frame_stats.h"

#include <algorithm>  // minmax_element
#include <iostream>
#include <numeric>  // accumulate
#include <optional>

std::optional<FrameStats> compute_stats(const std::vector<int>& frame) {
  if (frame.empty()) return std::nullopt;
  auto [min, max] = std::minmax_element(frame.begin(), frame.end());
  long long sum{};
  for (auto pix : frame) {
    sum += pix;
  }

  double mean = static_cast<double>(sum) / frame.size();
  return FrameStats{.min = *min, .max = *max, .mean = mean};
}