// tests/test_main.cpp
#include <gtest/gtest.h>

#include <optional>
#include <vector>

#include "frame_stats.h"

TEST(FrameStatsTest, HandlesBasicFrame) {
  std::vector<int> frame{10, 20, 30, 40, 50};

  auto result = compute_stats(frame);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->min(),10);
  EXPECT_EQ(result->max(), 50);
  EXPECT_DOUBLE_EQ(result->mean(),30.0);
  EXPECT_NEAR(result->stddev(),14.1421,1e-4);
  EXPECT_EQ(result->mode(), 10);
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
  EXPECT_EQ(*result, FrameStats(10, 10, 10.0, 0.0, 10));
}

TEST(FrameStatsTest, ModeTieTakesSmallest){
  std::vector<int> frame{3, 1, 3, 1};

  auto result = compute_stats(frame);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->mode(), 1);
}

TEST(FrameStatsTest, ModeIsMostFrequent){
  std::vector<int> frame{5, 7, 7, 9};

  auto result = compute_stats(frame);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->mode(), 7);
}

TEST(FrameStatsTest, StddevExactValue){
  std::vector<int> frame{2, 4, 4, 4, 5, 5, 7, 9};

  auto result = compute_stats(frame);
  ASSERT_TRUE(result.has_value());
  EXPECT_DOUBLE_EQ(result->stddev(), 2.0);
}

