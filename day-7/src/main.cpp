#include "helpers.hpp"
#include "logic.hpp"
#include <iostream>
#include <string>
#include <vector>

int part_one(const std::vector<std::string> &lines) {
  std::vector<std::string> new_tree = get_split_tree(lines);
  int splits = count_splits_in_split_tree(new_tree);

  return splits;
}

int main(int argc, char *argv[]) {
  try {
    std::string content = aoc::read_file(argv[1]);
    std::cout << "File loaded! Size: " << content.length() << std::endl;

    std::vector<std::string> lines = aoc::splitString(content, '\n');

    int result = part_one(lines);
    std::cout << "Part One: " << result << std::endl;

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
