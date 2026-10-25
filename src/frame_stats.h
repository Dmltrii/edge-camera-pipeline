#ifndef FRAME_STATS_H
#define FRAME_STATS_H

#include <cassert>
#include <optional>
#include <ostream>
#include <vector>

class FrameStats {
 public:
  FrameStats(int min, int max, double mean, double stddev, int mode)
      : m_min{min}, m_max{max}, m_mean{mean}, m_stddev{stddev}, m_mode{mode} {
    assert(min <= max);
    assert((min <= mean) && (mean <= max));
    assert((min <= mode) && (mode <= max));
    assert(stddev >= 0.0);
  }
  bool operator==(const FrameStats&) const = default;

  int range() const { return (m_max - m_min); }
  int min() const { return m_min; }
  int max() const { return m_max; }
  double mean() const { return m_mean; }
  double stddev() const { return m_stddev; }
  int mode() const { return m_mode; }

 private:
  int m_min{};
  int m_max{};
  double m_mean{};
  double m_stddev{};
  int m_mode{};
};

std::optional<FrameStats> compute_stats(const std::vector<int>& frame);

inline std::ostream& operator<<(std::ostream& os, const FrameStats& frame) {
  os << "(" << "min: " << frame.min() << ", max: " << frame.max()
     << ", mean: " << frame.mean() << ", range: " << frame.range()
     << ", std: " << frame.stddev() << ", mode: " << frame.mode() << ")";
  return os;
}

#endif
