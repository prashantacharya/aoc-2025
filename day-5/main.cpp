#include <fstream>
#include <iostream>
#include <omp.h>
#include <sstream>
#include <string>
#include <vector>

struct Range {
  unsigned long long start;
  unsigned long long end;
};

struct ParsedInput {
  std::vector<Range> fresh_ids;
  std::vector<unsigned long long> ids;
};

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

ParsedInput parse_input(const std::string &input) {
  std::vector<std::string> lines = split(input, '\n');

  std::vector<Range> fresh_ids;
  std::vector<unsigned long long> ids;

  size_t i = 0;
  for (i = 0; i < lines.size(); i++) {
    std::string line = lines[i];
    if (line.empty()) {
      break;
    }

    std::vector<std::string> tokens = split(line, '-');

    unsigned long long start_id = std::stoll(tokens[0]);
    unsigned long long end_id = std::stoll(tokens[1]);

    Range range{start_id, end_id};
    fresh_ids.push_back(range);
  }

  for (i = i + 1; i < lines.size(); i++) {
    std::string line = lines[i];
    if (line.empty()) {
      break;
    }

    ids.push_back(std::stoll(line));
  }

  return ParsedInput{fresh_ids, ids};
}

bool is_fresh(const std::vector<Range> &fresh_ids, unsigned long long id) {
  bool found = false;
#pragma omp parallel for
  for (size_t i = 0; i < fresh_ids.size(); i++) {
    Range range = fresh_ids[i];
    if (range.start <= id && range.end >= id) {
      found = true;
    }
  }

  return found;
}

int part_one(const ParsedInput &parsed_input) {
  int result = 0;

#pragma omp parallel for reduction(+ : result)
  for (size_t i = 0; i < parsed_input.ids.size(); i++) {
    if (is_fresh(parsed_input.fresh_ids, parsed_input.ids[i])) {
      result++;
    }
  }

  return result;
}

int part_two(const std::string &input) { return 0; }

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <input-file>" << std::endl;
    return 1;
  }

  std::ifstream input_file(argv[1]);
  if (!input_file.is_open()) {
    std::cerr << "Error opening the file." << std::endl;
    return 1;
  }

  std::stringstream buffer;
  buffer << input_file.rdbuf();
  std::string input_content = buffer.str();

  ParsedInput parsed_input = parse_input(input_content);
  // print_input(parsed_input);

  int p1_result = part_one(parsed_input);
  int p2_result = part_two(input_content);

  std::cout << "Part 1: " << p1_result << std::endl;
  std::cout << "Part 2: " << p2_result << std::endl;

  return 0;
}
