#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

const int LIMIT = 100;

struct Instruction {
  char direction;
  int steps;
};

int moveDial(int current, int step, int limit) {
  return (current + step % limit + limit) % limit;
}

std::pair<int, int> countDialReachingZero(int current, Instruction instruction,
                                          int limit) {
  auto step = 1;
  auto new_position = current;
  int count = 0;

  if (instruction.direction == 'L')
    step = -1;

  for (int i = 0; i < instruction.steps; i++) {
    new_position = moveDial(new_position, step, limit);

    if (new_position == 0) {
      count++;
    }
  }

  return {count, new_position};
}

int second_part(std::vector<Instruction> instructions) {
  auto current_position = 50;
  auto count = 0;

  for (auto instruction : instructions) {
    auto p = countDialReachingZero(current_position, instruction, 100);
    count += p.first;
    current_position = p.second;
  }

  return count;
}

int first_part(std::vector<Instruction> instructions) {
  auto current_position = 50;
  auto count = 0;

  for (auto instruction : instructions) {
    if (instruction.direction == 'L') {
      current_position = moveDial(current_position, -instruction.steps, 100);
    } else {
      current_position = moveDial(current_position, instruction.steps, 100);
    }

    if (current_position == 0) {
      count++;
    }
  }

  return count;
}

int main(int argc, char *argv[]) {
  std::string input_file;
  if (argc != 2) {
    input_file = "example-input";
  } else {
    input_file = argv[1];
  }

  std::ifstream file(input_file);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << input_file << std::endl;
    return 1;
  }

  std::string line;
  std::vector<Instruction> instructions;
  while (std::getline(file, line)) {
    Instruction instruction;

    instruction.direction = line[0];
    instruction.steps = std::stoi(line.substr(1));

    instructions.push_back(instruction);
  }

  int password = first_part(instructions);
  int second_password = second_part(instructions);

  std::cout << "First part: " << password << std::endl;
  std::cout << "Second part: " << second_password << std::endl;

  return 0;
}
