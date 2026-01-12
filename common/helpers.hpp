#pragma once
#include <string>
#include <vector>

namespace aoc {
std::string read_file(const std::string &filename);

std::vector<std::string> splitString(const std::string &s, char delimiter);
} // namespace aoc
