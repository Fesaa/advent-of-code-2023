#include <cstdio>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

struct LandScape {
  vector<vector<char>> grid;

  int verticalCheck(int a, int b);
  int isVerticalReflection(int v);
  int verticalReflectionFactor(int v1, int v2);
  int horizontalCheck(int a, int b);
  int isHorizontalReflection(int h);
  int horizontalReflectionFactor(int v1, int v2);
};

int part1(vector<LandScape> landscapes);
int part2(vector<LandScape> landscapes);

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

  printf("Part 1: %d\n", part1(landscapes));
  printf("Part 2: %d\n", part2(landscapes));
}

int part2(vector<LandScape> landscapes) {
  int sumV = 0;
  int sumH = 0;
  for (LandScape l : landscapes) {
    sumV += l.verticalReflectionFactor(0, 1);
    sumH += l.horizontalReflectionFactor(0, 1);
  }
  return sumV + 100 * sumH;
}

int part1(vector<LandScape> landscapes) {
  int sumV = 0;
  int sumH = 0;
  for (LandScape l : landscapes) {
    sumV += l.verticalReflectionFactor(0, 0);
    sumH += l.horizontalReflectionFactor(0, 0);
  }
  return sumV + 100 * sumH;
}

int LandScape::verticalReflectionFactor(int v1, int v2) {
  for (int i = 0; i < grid[0].size() - 1; i++) {
    int c = verticalCheck(i, i + 1);
    int r = isVerticalReflection(i);
    if ((c == v1 && r == v2) || (c == v2 && r == v1)) {
      return i + 1;
    }
  }
  return 0;
}

int LandScape::isVerticalReflection(int line) {
  int a = line;
  int b = line + 1;
  int diff = 0;
  while (a > 0 && b < grid[0].size() - 1) {
    a--;
    b++;
    diff += verticalCheck(a, b);
    if (diff > 1) {
      return 2;
    }
  }
  return diff;
}

int LandScape::verticalCheck(int a, int b) {
  int diff = 0;
  for (int i = 0; i < grid.size(); i++) {
    if (grid[i][a] != grid[i][b]) {
      diff++;
    }
    if (diff > 1) {
      return 2;
    }
  }
  return diff;
}

int LandScape::horizontalReflectionFactor(int v1, int v2) {
  for (int i = 0; i < grid.size() - 1; i++) {
    int c = horizontalCheck(i, i + 1);
    int r = isHorizontalReflection(i);
    if ((c == v1 && r == v2) || (c == v2 && r == v1)) {
      return i + 1;
    }
  }
  return 0;
}

int LandScape::isHorizontalReflection(int h) {
  int a = h;
  int b = h + 1;
  int diff = 0;
  while (a > 0 && b < grid.size() - 1) {
    a--;
    b++;
    diff += horizontalCheck(a, b);
    if (diff > 1) {
      return 2;
    }
  }
  return diff;
}

int LandScape::horizontalCheck(int a, int b) {
  int diff = 0;
  for (int i = 0; i < grid[0].size(); i++) {
    if (grid[a][i] != grid[b][i]) {
      diff++;
    }
    if (diff > 1) {
      return 2;
    }
  }
  return diff;
}
