#ifndef FRAME_STATS_H
#define FRAME_STATS_H

#include <optional>
#include <ostream>
#include <vector>

struct FrameStats {
  int min{};
  int max{};
  double mean{};
  int range() const { return max - min; }
};

std::optional<FrameStats> compute_stats(const std::vector<int>& frame);

inline std::ostream& operator<<(std::ostream& os, const FrameStats& frame) {
  os << "(" << "min: " << frame.min << ", max: " << frame.max
     << ", mean: " << frame.mean << ", range: " << frame.range() << ")";
  return os;
}

#endif