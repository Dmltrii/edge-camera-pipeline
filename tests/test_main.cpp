// tests/test_main.cpp
#include <gtest/gtest.h>

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include "frame_stats.h"

std::string reverseString(std::string s) {
  std::reverse(s.begin(), s.end());
  return s;
}

TEST(ReverseStringTest, HandlesBasicInput) {
  EXPECT_EQ(reverseString("abc"), "cba");
}

TEST(FrameStatsTest, HandlesBasicFrame) {
  std::vector<int> frame{10, 20, 30, 40, 50};

  auto result = compute_stats(frame);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, FrameStats(10, 50, 30.0));
}

TEST(FrameStatsTest, HandlesEmptyFrame) {
  std::vector<int> frame{};

  auto result = compute_stats(frame);

  EXPECT_EQ(result, std::nullopt);
}

TEST(FrameStatsTest, HandlesOneElementFrame) {
  std::vector<int> frame{10};

  auto result = compute_stats(frame);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, FrameStats(10, 10, 10.0));
}

