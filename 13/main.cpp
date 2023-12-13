#include <cstdio>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

struct LandScape {
  vector<vector<char>> grid;

  bool verticalCheck(int a, int b);
  bool isVerticalReflection(int v);
  int verticalReflectionFactor();
  bool horizontalCheck(int a, int b);
  bool isHorizontalReflection(int h);
  int horizontalReflectionFactor();
};

int part1(vector<LandScape> landscapes);

int main() {
  // ifstream file("sample");
  ifstream file("input");

  if (!file.is_open()) {
    printf("Could not open file\n");
    return 1;
  }

  vector<LandScape> landscapes;
  vector<vector<char>> grid;
  string line;

  while (getline(file, line)) {
    if (line == "") {
      LandScape l = LandScape{.grid = grid};
      landscapes.push_back(l);
      grid = {};
      continue;
    }
    vector<char> v;
    copy(line.begin(), line.end(), back_inserter(v));
    grid.push_back(v);
  }
  landscapes.push_back(LandScape{.grid = grid});

  printf("Found %zu landscapes\n", landscapes.size());

  printf("Part 1: %d\n", part1(landscapes));
}

int part1(vector<LandScape> landscapes) {
  int sumV = 0;
  int sumH = 0;
  for (LandScape l : landscapes) {
    sumV += l.verticalReflectionFactor();
    sumH += l.horizontalReflectionFactor();
  }
  return sumV + 100 * sumH;
}

int LandScape::verticalReflectionFactor() {
  for (int i = 0; i < grid[0].size() - 1; i++) {
    if (verticalCheck(i, i + 1) && isVerticalReflection(i)) {
      return i + 1;
    }
  }
  return 0;
}

bool LandScape::isVerticalReflection(int line) {
  int a = line;
  int b = line + 1;
  while (a > 0 && b < grid[0].size() - 1) {
    a--;
    b++;
    if (!verticalCheck(a, b)) {
      return false;
    }
  }
  return true;
}

bool LandScape::verticalCheck(int a, int b) {
  for (int i = 0; i < grid.size(); i++) {
    if (grid[i][a] != grid[i][b]) {
      return false;
    }
  }
  return true;
}

int LandScape::horizontalReflectionFactor() {
  for (int i = 0; i < grid.size() - 1; i++) {
    if (horizontalCheck(i, i + 1) && isHorizontalReflection(i)) {
      return i + 1;
    }
  }
  return 0;
}

bool LandScape::isHorizontalReflection(int h) {
  int a = h;
  int b = h + 1;
  while (a > 0 && b < grid.size() - 1) {
    a--;
    b++;
    if (!horizontalCheck(a, b)) {
      return false;
    }
  }
  return true;
}

bool LandScape::horizontalCheck(int a, int b) {
  for (int i = 0; i < grid[0].size(); i++) {
    if (grid[a][i] != grid[b][i]) {
      return false;
    }
  }
  return true;
}
