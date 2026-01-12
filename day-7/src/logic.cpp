#include "logic.hpp"

std::vector<std::string> get_split_tree(std::vector<std::string> lines) {
  std::vector<std::string> result = lines;

  for (size_t i = 0; i < lines.size(); i++) {
    for (size_t j = 0; j < lines[i].size(); j++) {
      if (result[i][j] == 'S') {
        result[i + 1][j] = '|';
        continue;
      }

      if (i > 0 && result[i][j] == '^' && result[i - 1][j] == '|') {
        result[i][j - 1] = '|';
        result[i][j + 1] = '|';
        continue;
      }

      if (i > 0 && result[i - 1][j] == '|') {
        result[i][j] = '|';
        continue;
      }
    }
  }

  return result;
}

int count_splits_in_split_tree(const std::vector<std::string> &lines) {
  int result = 0;

  for (size_t i = 0; i < lines.size(); i++) {
    for (size_t j = 0; j < lines[i].size(); j++) {
      if (i > 0 && lines[i][j] == '^' && lines[i - 1][j] == '|') {
        result++;
        continue;
      }
    }
  }

  return result;
}

int count_splits(const std::vector<std::string> &lines) {
  std::vector<std::string> new_tree = lines;
  int splits = 0;
  for (size_t i = 0; i < new_tree.size(); i++) {

    for (size_t j = 0; j < new_tree[i].size(); j++) {
      if (new_tree[i][j] == 'S') {
        new_tree[i + 1][j] = '|';
        continue;
      }

      if (i > 0 && new_tree[i][j] == '^' && new_tree[i - 1][j] == '|') {
        new_tree[i][j - 1] = '|';
        new_tree[i][j + 1] = '|';
        splits++;
        continue;
      }

      if (i > 0 && new_tree[i - 1][j] == '|') {
        new_tree[i][j] = '|';
        continue;
      }
    }
  }

  return splits;
}
