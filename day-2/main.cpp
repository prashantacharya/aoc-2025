#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Range {
  size_t start;
  size_t end;
};

bool isRepeatedSubstring(const std::string &str) {
  std::string doubledStr = str + str;

  // remove first and last character
  std::string trimmed = doubledStr.substr(1, doubledStr.length() - 2);

  return trimmed.find(str) != std::string::npos;
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

size_t processRange(Range range) {
  size_t result = 0;

#pragma omp parallel for reduction(+ : result)
  for (size_t i = range.start; i <= range.end; i++) {
    auto strNum = std::to_string(i);
    auto strLen = strNum.length();

    if (strLen % 2 != 0) {
      continue;
    }

    int halfLen = strLen / 2;

    std::string strNumLeft = strNum.substr(0, halfLen);
    std::string strNumRight = strNum.substr(halfLen);

    if (strNumLeft == strNumRight) {
      result += i;
    }
  }

  return result;
}

size_t processRangePart2(Range range) {
  size_t result = 0;

#pragma omp parallel for reduction(+ : result)
  for (size_t i = range.start; i <= range.end; i++) {
    auto strNum = std::to_string(i);

    if (isRepeatedSubstring(strNum)) {
      result += i;
    }
  }

  return result;
}

size_t partOne(std::vector<std::string> input) {
  size_t result = 0;
  std::vector<Range> ranges;

  for (size_t i = 0; i < input.size(); i++) {
    auto range = input[i];
    auto rangeSplit = splitString(range, '-');
    size_t start = std::stoll(rangeSplit[0]);
    size_t end = std::stoll(rangeSplit[1]);

    Range newRange{start, end};
    result += processRange(newRange);
  }

  return result;
}

size_t partTwo(std::vector<std::string> input) {
  size_t result = 0;
  std::vector<Range> ranges;

  for (size_t i = 0; i < input.size(); i++) {
    auto range = input[i];
    auto rangeSplit = splitString(range, '-');
    size_t start = std::stoll(rangeSplit[0]);
    size_t end = std::stoll(rangeSplit[1]);

    Range newRange{start, end};
    result += processRangePart2(newRange);
  }

  return result;
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "Please provide input file" << std::endl;
    return 1;
  }

  std::ifstream inputFile(argv[1]);
  std::string line;

  std::vector<std::string> inputRanges;

  while (std::getline(inputFile, line)) {
    auto inputRange = splitString(line, ',');
    inputRanges.insert(inputRanges.end(), inputRange.begin(), inputRange.end());
  }

  auto partOneResult = partOne(inputRanges);
  auto partTwoResult = partTwo(inputRanges);

  std::cout << "Part One: " << partOneResult << std::endl;
  std::cout << "Part Two: " << partTwoResult << std::endl;

  return 0;
}
