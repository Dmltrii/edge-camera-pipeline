#ifndef FRAME_STATS_H
#define FRAME_STATS_H

#include <optional>
#include <vector>

struct FrameStats {
  int min{};
  int max{};
  double mean{};
  int range() const { return max - min; }
};

std::optional<FrameStats> compute_stats(const std::vector<int>& frame);

#endif