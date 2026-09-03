#ifndef FRAME_STATS_H
#define FRAME_STATS_H

#include <cassert>
#include <optional>
#include <ostream>
#include <vector>

class FrameStats {
 public:
  FrameStats(int min, int max, double mean)
      : m_min{min}, m_max{max}, m_mean{mean} {
    assert(min <= max);
    assert((min <= mean) && (mean <= max));
  };
  bool operator==(const FrameStats&) const = default;

  int range() const { return (m_max - m_min); }
  int min() const { return m_min; }
  int max() const { return m_max; }
  double mean() const { return m_mean; }

 private:
  int m_min{};
  int m_max{};
  double m_mean{};
};

std::optional<FrameStats> compute_stats(const std::vector<int>& frame);

inline std::ostream& operator<<(std::ostream& os, const FrameStats& frame) {
  os << "(" << "min: " << frame.min() << ", max: " << frame.max()
     << ", mean: " << frame.mean() << ", range: " << frame.range() << ")";
  return os;
}

#endif

