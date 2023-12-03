#include <cctype>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

bool isSymbol(char c) { return !isdigit(c) && c != '.'; }

bool validDigit(int rowIndex, int startIndex, int endIndex,
                std::vector<std::vector<char>> &grid);

int part1(std::vector<std::vector<char>> grid);

int main() {
  std::ifstream inputFile("input.txt");
  if (!inputFile.is_open()) {
    printf("Error opening the file!\n");
    return 1;
  }

  std::vector<std::vector<char>> grid = {};

  std::string line;
  int i = 0;
  while (std::getline(inputFile, line)) {
    std::vector<char> row = {};

    for (int i = 0; i < line.length(); i++) {
      char current = line[i];
      row.push_back(current);
    }

    grid.push_back(row);
  }

  inputFile.close();

  int sum = part1(grid);
  printf("Sum: %d\n", sum);

  return 0;
}

int part1(std::vector<std::vector<char>> grid) {
  int sum = 0;

  for (int idxRow = 0; idxRow < grid.size(); idxRow++) {
    std::vector<char> row = grid[idxRow];
    int startIndex = -1;
    int endIndex = -1;
    int digit = 0;

    for (int idxCol = 0; idxCol < row.size(); idxCol++) {
      char c = row[idxCol];
      if (!isdigit(c)) {
        if (digit != 0 && validDigit(idxRow, startIndex, endIndex, grid)) {
          sum += digit;
        }
        digit = 0;
        startIndex = -1;
        endIndex = -1;
        continue;
      }

      digit = digit * 10 + (c - '0');
      if (startIndex == -1) {
        startIndex = idxCol;
      } else {
        endIndex = idxCol;
      }
    }

    if (validDigit(idxRow, startIndex, endIndex, grid)) {
      sum += digit;
    }
  }
  return sum;
}

bool validDigit(int rowIndex, int startIndex, int endIndex,
                std::vector<std::vector<char>> &grid) {
  if (endIndex == -1) {
    endIndex = startIndex;
  }

  int adjustedEndIndex;
  if (endIndex == grid[rowIndex].size() - 1) {
    adjustedEndIndex = endIndex;
  } else {
    adjustedEndIndex = endIndex + 1;
  }
  int adjustedStartIndex;
  if (startIndex == 0) {
    adjustedStartIndex = startIndex;
  } else {
    adjustedStartIndex = startIndex - 1;
  }

  // Above
  if (rowIndex > 0) {
    std::vector<char> rowAbove = grid[rowIndex - 1];
    for (int i = adjustedStartIndex; i <= adjustedEndIndex; i++) {
      if (isSymbol(rowAbove[i])) {
        return true;
      }
    }
  }

  // Left
  if (startIndex > 0) {
    if (isSymbol(grid[rowIndex][startIndex - 1])) {
      return true;
    }
  }

  // Right
  if (endIndex < grid[rowIndex].size() - 1) {
    if (isSymbol(grid[rowIndex][endIndex + 1])) {
      return true;
    }
  }

  // Below
  if (rowIndex < grid.size() - 1) {
    std::vector<char> rowBelow = grid[rowIndex + 1];
    for (int i = adjustedStartIndex; i <= adjustedEndIndex; i++) {
      if (isSymbol(rowBelow[i])) {
        return true;
      }
    }
  }

  return false;
}
