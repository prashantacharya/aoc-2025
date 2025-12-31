#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <omp.h>

int processStringPartOne(std::string line) {
  int largestFirst = 0;
  int largestFirstIndex = -1;
  int largestSecond = 0;

  for (size_t i = 0; i < line.size() - 1; i++) {
    int num = std::stoi(line.substr(i, 1));

    if (num > largestFirst) {
      largestFirst = num;
      largestFirstIndex = i;
    }
  }

  for (size_t i = largestFirstIndex + 1; i < line.size(); i++) {
    int num = std::stoi(line.substr(i, 1));
    if (num > largestSecond) {
      largestSecond = num;
    }
  }

  return largestFirst * 10 + largestSecond;
}


unsigned long long processStringPartTwo(const std::string& line) {
  const int K = 12;
  int n = line.size();
  int start = 0;

  unsigned long long result = 0;

  for (int remaining = K; remaining > 0; remaining--) {
    int maxDigit = -1;
    int maxIndex = start;

    // limit ensures enough characters remain
    int limit = n - remaining;

    for (int i = start; i <= limit; i++) {
      int d = line[i] - '0';
      if (d > maxDigit) {
        maxDigit = d;
        maxIndex = i;
      }
    }

    result = result * 10 + maxDigit;
    start = maxIndex + 1;
  }

  return result;
}


int partOne(std::vector<std::string> lines) {
  int result = 0;

  #pragma omp parallel for reduction(+:result)
  for (size_t i = 0; i < lines.size(); i++) {
    result += processStringPartOne(lines[i]);
  }

  return result;
}


unsigned long long partTwo(std::vector<std::string> lines) {
  unsigned long long result = 0;

  #pragma omp parallel for reduction(+:result)
  for (size_t i = 0; i < lines.size(); i++) {
    result += processStringPartTwo(lines[i]);
  }

  return result;
}

int main(int argc, char** argv) {

  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <input-file>" << std::endl;
    return 1;
  }

  std::ifstream input(argv[1]);
  std::string line;
  std::vector<std::string> lines;

  while (std::getline(input, line)) {
    lines.push_back(line);
  }

  int resultPartOne = partOne(lines);
  auto resultPartTwo = partTwo(lines);

  std::cout << "Part One: " << resultPartOne << std::endl;
  std::cout << "Part Two: " << resultPartTwo << std::endl;

  return 0;
}
