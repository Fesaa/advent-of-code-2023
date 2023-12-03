#include <cctype>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

bool isSymbol(char c) { return !isdigit(c) && c != '.'; }

bool validDigit(int rowIndex, int startIndex, int endIndex,
                std::vector<std::vector<char>> &grid);

int gearProduct(int row, int column, std::vector<std::vector<char>> grid);
int part1(std::vector<std::vector<char>> grid);
int part2(std::vector<std::vector<char>> grid);

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
  int sum2 = part2(grid);
  printf("Sum: %d\n", sum);
  printf("Sum2: %d\n", sum2);

  return 0;
}

int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

bool isNeighbour(int start, int end, int house) {
  if (start == house || end == house) {
    return true;
  }

  if (start < house && end > house) {
    return true;
  }

  if (start == house + 1) {
    return true;
  }

  if (end == house - 1) {
    return true;
  }

  return false;
}

int gearProduct(int rowIndex, int columnIndex,
                std::vector<std::vector<char>> grid) {

  int prod = 1;
  int adders = 0;

  std::vector<std::vector<char>> rows = {};
  if (rowIndex > 0) {
    rows.push_back(grid[rowIndex - 1]);
  }

  if (rowIndex < grid.size() - 1) {
    rows.push_back(grid[rowIndex + 1]);
  }

  rows.push_back(grid[rowIndex]);

  for (std::vector<char> row : rows) {
    int start = max(columnIndex - 3, 0);
    int end = min(columnIndex + 3, row.size() - 1);

    int startIndex = -1;
    int endIndex = -1;
    int digit = 0;

    for (int pos = start; pos <= end; pos++) {
      char c = row[pos];
      if (isdigit(c)) {
        digit = digit * 10 + (c - '0');
        if (startIndex == -1) {
          startIndex = pos;
        } else {
          endIndex = pos;
        }
      } else if (digit != 0) {
        if (endIndex == -1) {
          endIndex = startIndex;
        }

        if (isNeighbour(startIndex, endIndex, columnIndex)) {
          prod *= digit;
          adders++;
        }

        digit = 0;
        startIndex = -1;
        endIndex = -1;
      }
    }

    if (isNeighbour(startIndex, endIndex, columnIndex)) {
      prod *= digit;
      adders++;
    }
  }

  if (adders != 2) {
    return 0;
  }

  return prod;
}

int part2(std::vector<std::vector<char>> grid) {
  int sum = 0;

  for (int i = 0; i < grid.size(); i++) {
    std::vector<char> row = grid[i];

    for (int j = 0; j < row.size(); j++) {
      char c = row[j];

      if (c == '*') {
        sum += gearProduct(i, j, grid);
      }
    }
  }

  return sum;
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
