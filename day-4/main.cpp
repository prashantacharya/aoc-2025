#include <fstream>
#include <iostream>
#include <omp.h>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> splitString(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::stringstream ss(s);
  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

std::string join(const std::vector<std::string> &vec,
                 const std::string &delimiter) {
  if (vec.empty())
    return "";

  // Optimization: Pre-calculate total size to avoid reallocations
  size_t total_size = 0;
  for (const auto &s : vec)
    total_size += s.size() + delimiter.size();

  std::string result;
  result.reserve(total_size);

  for (size_t i = 0; i < vec.size(); ++i) {
    result += vec[i];
    if (i < vec.size() - 1) {
      result += delimiter;
    }
  }
  return result;
}

std::string add_padding(const std::vector<std::string> &original) {
  if (original.empty())
    return {};

  int cols = original[0].size();

  std::vector<std::string> padded;

  // 1. Create a top border row: "..."
  // Length is cols + 2 to account for the side borders
  std::string horizontalBorder(cols + 2, '.');

  // 2. Add the top border
  padded.push_back(horizontalBorder);

  // 3. Add original rows with side padding
  for (const std::string &row : original) {
    padded.push_back("." + row + ".");
  }

  // 4. Add the bottom border
  padded.push_back(horizontalBorder);

  return join(padded, "\n");
}

int count_adjacent_rows(const std::vector<std::string> &rows, int row,
                        int col) {
  int adjacent_count = 0;

  if (rows[row - 1][col - 1] == '@') {
    adjacent_count++;
  }

  if (rows[row - 1][col] == '@') {
    adjacent_count++;
  }

  if (rows[row - 1][col + 1] == '@') {
    adjacent_count++;
  }

  if (rows[row][col - 1] == '@') {
    adjacent_count++;
  }

  if (rows[row][col + 1] == '@') {
    adjacent_count++;
  }

  if (rows[row + 1][col - 1] == '@') {
    adjacent_count++;
  }

  if (rows[row + 1][col] == '@') {
    adjacent_count++;
  }

  if (rows[row + 1][col + 1] == '@') {
    adjacent_count++;
  }

  return adjacent_count;
}

int part_one(const std::string &input) {
  auto padded_input = add_padding(splitString(input, '\n'));
  auto input_rows = splitString(padded_input, '\n');

  size_t rows = input_rows.size();
  int cols = input_rows[0].size();

  int count = 0;

  for (size_t i = 1; i < rows - 1; i++) {
    for (int j = 1; j < cols - 1; j++) {
      if (input_rows[i][j] == '@' &&
          count_adjacent_rows(input_rows, i, j) < 4) {
        count++;
      }
    }
  }

  return count;
}

int part_two(const std::string &input) {
  auto padded_input = add_padding(splitString(input, '\n'));
  auto input_rows = splitString(padded_input, '\n');

  int rows = input_rows.size();
  int cols = input_rows[0].size();

  int count = 0;
  int new_count = 1;

  while (new_count != 0) {
    new_count = 0;

    for (int i = 1; i < rows - 1; i++) {
      for (int j = 1; j < cols - 1; j++) {
        if (input_rows[i][j] == '@' &&
            count_adjacent_rows(input_rows, i, j) < 4) {
          new_count++;

          input_rows[i][j] = 'x';
        }
      }
    }

    count += new_count;
  }

  return count;
}

int main(int argc, const char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <input-file>" << std::endl;
    return 1;
  }

  std::string input_file = argv[1];

  std::ifstream input(input_file);
  std::string line;

  std::string input_lines;

  int no_of_lines = 0;

  while (std::getline(input, line)) {
    input_lines += line + "\n";

    no_of_lines++;
  }

  input.close();

  auto partOneOutput = part_one(input_lines);
  auto partTwoOutput = part_two(input_lines);

  std::cout << "Part One: " << partOneOutput << std::endl;
  std::cout << "Part Two: " << partTwoOutput << std::endl;

  return 0;
}
