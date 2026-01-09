#include "helpers.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace aoc {
std::string read_file(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + filename);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}
} // namespace aoc
