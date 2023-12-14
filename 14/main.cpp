#include <cstdio>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

int part1(vector<vector<char>> grid);
int part2(vector<vector<char>> grid, int rolls);

void rollNorth(vector<vector<char>> &grid);
void rollSouth(vector<vector<char>> &grid);
void rollEast(vector<vector<char>> &grid);
void rollWest(vector<vector<char>> &grid);

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
  printf("Part 2: %d\n", part2(grid, 1000000000));
}

void rollNorth(vector<vector<char>> &grid) {
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
}
void rollSouth(vector<vector<char>> &grid) {
  int lineSize = grid[0].size();
  for (int i = grid.size() - 1; i >= 0; i--) {
    for (int j = 0; j < lineSize; j++) {
      if (grid[i][j] != 'O') {
        continue;
      }

      char cur = grid[i][j];
      int pos = i + 1;
      while (pos < grid.size() && grid[pos][j] == '.') {
        pos++;
      }

      grid[i][j] = '.';
      grid[pos - 1][j] = 'O';
    }
  }
}
void rollEast(vector<vector<char>> &grid) {
  int lineSize = grid[0].size();
  for (int i = 0; i < grid.size(); i++) {
    for (int j = lineSize - 1; j >= 0; j--) {
      if (grid[i][j] != 'O') {
        continue;
      }

      char cur = grid[i][j];
      int pos = j + 1;
      while (pos < grid.size() && grid[i][pos] == '.') {
        pos++;
      }

      grid[i][j] = '.';
      grid[i][pos - 1] = 'O';
    }
  }
}
void rollWest(vector<vector<char>> &grid) {
  int lineSize = grid[0].size();
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 1; j < lineSize; j++) {
      if (grid[i][j] != 'O') {
        continue;
      }

      char cur = grid[i][j];
      int pos = j - 1;
      while (pos >= 0 && grid[i][pos] == '.') {
        pos--;
      }

      grid[i][j] = '.';
      grid[i][pos + 1] = 'O';
    }
  }
}

int part2(vector<vector<char>> grid, int rolls) {

  map<vector<vector<char>>, int> seen;

  for (int i = 0; i < rolls; i++) {
    rollNorth(grid);
    rollWest(grid);
    rollSouth(grid);
    rollEast(grid);

    if (seen.find(grid) != seen.end()) {
      int cycle = i - seen[grid];
      int remaining = (rolls - i) % cycle;
      i = rolls - remaining;
      continue;
    }

    seen[grid] = i;
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
