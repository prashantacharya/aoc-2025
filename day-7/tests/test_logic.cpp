#include "logic.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Helper to create the vector for testing
std::vector<std::string> get_test_lines() {

  std::vector<std::string> tree_lines = {
      ".......S.......", ".......|.......", "......|^|......",
      "......|.|......", ".....|^|^|.....", ".....|.|.|.....",
      "....|^|^|^|....", "....|.|.|.|....", "...|^|^|||^|...",
      "...|.|.|||.|...", "..|^|^|||^|^|..", "..|.|.|||.|.|..",
      ".|^|||^||.||^|.", ".|.|||.||.||.|.", "|^|^|^|^|^|||^|",
      "|.|.|.|.|.|||.|"};

  return tree_lines;
}

std::vector<std::string> get_test_lines_new() {
  return {".......S.......", "...............", ".......^.......",
          "...............", "......^.^......", "...............",
          ".....^.^.^.....", "...............", "....^.^...^....",
          "...............", "...^.^...^.^...", "...............",
          "..^...^.....^..", "...............", ".^.^.^.^.^...^.",
          "..............."};
}

TEST(Day07CountSplitsTest, CountSplitsInExampleInput) {
  auto lines = get_test_lines_new();

  EXPECT_EQ(count_splits(lines), 21);
}

TEST(Day07CheckStartingPoint, CheckStartingPoint) {
  std::vector<std::string> input = {
      "..S..",
      ".....",
  };
  std::vector<std::string> output = {
      "..S..",
      "..|..",
  };

  EXPECT_EQ(get_split_tree(input), output);
}

TEST(CheckIfDaySplitWorksCorrectly, CheckIfDaySplitWorksCorrectly) {
  std::vector<std::string> input = {
      "..S..",
      ".....",
      "..^..",
      ".....",
  };

  std::vector<std::string> output = {
      "..S..",
      "..|..",
      ".|^|.",
      ".|.|.",
  };

  EXPECT_EQ(get_split_tree(input), output);
}
