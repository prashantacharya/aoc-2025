#include "logic.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Helper to create the vector for testing
std::vector<std::string> get_test_lines() {
  return {"123 328  51 64 ", " 45 64  387 23 "};
}

TEST(Day06LogicTest, HandlesExampleInputSpaces) {
  auto lines = get_test_lines();

  // Column 3 is a space in both lines
  EXPECT_TRUE(contains_all_spaces(lines, 3));

  // Column 7 is a space in both lines (between 328 and 51 block)
  EXPECT_TRUE(contains_all_spaces(lines, 7));

  // Column 0 is NOT all spaces (Line 1 has '1')
  EXPECT_FALSE(contains_all_spaces(lines, 0));
}

TEST(Day06LogicTest, ParsesVerticalNumbers) {
  auto lines = get_test_lines();

  // Index 0: '1' and ' ' -> "1"
  EXPECT_EQ(get_number_at_index(lines, 0), 1);

  // Index 1: '2' and '4' -> "24"
  EXPECT_EQ(get_number_at_index(lines, 1), 24);

  // Index 4: '3' and '6' (from 328 and 64) -> "36"
  EXPECT_EQ(get_number_at_index(lines, 4), 36);

  // Index 8: ' ' and '3' (from 387) -> "3"
  EXPECT_EQ(get_number_at_index(lines, 8), 3);
}
