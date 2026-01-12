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

std::vector<std::string> splitString(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::stringstream ss(s);
  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

} // namespace aoc
