#include "logic.hpp"
#include <fstream>
#include <iostream>
#include <omp.h>
#include <sstream>
#include <vector>

std::vector<std::string> parse_number_line(const std::string &line) {
  std::vector<std::string> numbers;
  size_t current = 0;

  while (current < line.size()) {
    if (line[current] == ' ') {
      current++;
      continue;
    }

    std::string number_str;
    while (current < line.size() && line[current] != ' ') {
      number_str += line[current];
      current++;
    }
    numbers.push_back(number_str);
  }

  return numbers;
}

std::vector<char> parse_operator_line(const std::string &line) {
  std::vector<char> operators;

  for (auto c : line) {
    if (c != ' ') {
      operators.push_back(c);
    }
  }

  return operators;
}

unsigned long long
apply_operator_at_index(const std::vector<std::vector<std::string>> &numbers,
                        const char &op, int &index) {
  unsigned long long result = op == '+' ? 0 : 1;

  for (size_t i = 0; i < numbers.size(); i++) {
    if (op == '+') {
      result += std::stoull(numbers[i][index]);
    } else if (op == '*') {
      result *= std::stoull(numbers[i][index]);
    }
  }

  return result;
}

unsigned long long
part_one(const std::vector<std::vector<std::string>> &numbers,
         const std::vector<char> &operators) {

  unsigned long long result = 0;

#pragma omp parallel for reduction(+ : result)
  for (int i = 0; i < operators.size(); i++) {
    result += apply_operator_at_index(numbers, operators[i], i);
  }

  return result;
}

unsigned long long part_two(const std::vector<std::string> &lines,
                            const std::vector<char> &operators,
                            int max_line_length = 0) {
  unsigned long long result = 0;
  int operator_index = 0;
  unsigned long long current_result = operators[operator_index] == '+' ? 0 : 1;
  bool in_number_block = false;

  for (int i = 0; i < max_line_length; i++) {
    if (contains_all_spaces(lines, i)) {

      if (in_number_block) {
        operator_index++;
        result += current_result;
        current_result = operators[operator_index] == '+' ? 0 : 1;
        in_number_block = false;
      }

      continue;
    }

    in_number_block = true;

    auto number_at_current_col = get_number_at_index(lines, i);

    if (operators[operator_index] == '+') {
      current_result += number_at_current_col;
    } else if (operators[operator_index] == '*') {
      current_result *= number_at_current_col;
    }
  }

  if (in_number_block) {
    result += current_result;
  }

  return result;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./main "
                 "<input-file>"
              << std::endl;
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input.is_open()) {
    std::cerr << "Failed to open "
                 "input file"
              << std::endl;
    return 1;
  }

  std::string line;

  std::vector<std::vector<std::string>> numbers;
  std::vector<char> operators;

  std::string file_content;
  size_t max_line_length = 0;

  std::vector<std::string> lines;

  while (std::getline(input, line)) {
    if (input.peek() == EOF) {
      operators = parse_operator_line(line);
    } else {
      auto parsed_numbers = parse_number_line(line);
      numbers.push_back(parsed_numbers);
      max_line_length = std::max(max_line_length, line.size());
      lines.push_back(line);
    }
  }

  auto part_one_result = part_one(numbers, operators);
  std::cout << "Part One: " << part_one_result << std::endl;
  std::cout << "Part Two: " << part_two(lines, operators, max_line_length)
            << std::endl;

  return 0;
}
