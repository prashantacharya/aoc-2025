#include "logic.hpp"

#include <string>
#include <vector>

bool contains_all_spaces(const std::vector<std::string> &lines, int index) {
  for (const auto &line : lines) {
    if (index >= line.length() || line[index] != ' ') {
      return false;
    }
  }
  return true;
}

unsigned long long get_number_at_index(const std::vector<std::string> &lines,
                                       int index) {
  std::string number_str;
  for (const auto &line : lines) {
    if (index < line.length() && line[index] != ' ') {
      number_str += line[index];
    }
  }
  return number_str.empty() ? 0 : std::stoull(number_str);
}
