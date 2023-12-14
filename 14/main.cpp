#include <cstdio>
#include <fstream>
#include <vector>

using namespace std;

int part1(vector<vector<char>> grid);

int main() {
  // ifstream file("sample");
  ifstream file("input");

  if (!file.is_open()) {
    printf("Could not open file\n");
    return 1;
  }

  vector<vector<char>> grid;

  for (string line; getline(file, line);) {
    vector<char> row;
    for (char c : line) {
      row.push_back(c);
    }
    grid.push_back(row);
  }

  printf("Part 1: %d\n", part1(grid));
}

int part1(vector<vector<char>> grid) {
  int lineSize = grid[0].size();
  for (int i = 1; i < grid.size(); i++) {
    for (int j = 0; j < lineSize; j++) {
      if (grid[i][j] != 'O') {
        continue;
      }

      char cur = grid[i][j];
      int pos = i - 1;
      while (pos >= 0 && grid[pos][j] == '.') {
        pos--;
      }

      grid[i][j] = '.';
      grid[pos + 1][j] = 'O';
    }
  }

  int sum = 0;
  int weight = grid.size();
  for (vector<char> row : grid) {
    for (char c : row) {
      if (c == 'O') {
        sum += weight;
      }
    }
    weight--;
  }

  return sum;
}
