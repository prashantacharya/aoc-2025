#include "helpers.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  try {
    std::string content = aoc::read_file(argv[1]);
    std::cout << "File loaded! Size: " << content.length() << std::endl;

    // Your logic here...

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
