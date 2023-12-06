#include <cmath>
#include <cstdio>
#include <fstream>
#include <vector>

using std::string;
using std::vector;

struct Range {
  double lowerbound;
  double upperbound;
};

struct Race {
  int time;
  int distance;

  double d(double tw) { return tw * (time - tw); }
  Range getWinningRange() {
    double lower = (time - pow(pow(time, 2) - 4 * distance, (double)1 / 2)) / 2;
    double upper = (time + pow(pow(time, 2) - 4 * distance, (double)1 / 2)) / 2;
    return Range{
        .lowerbound = lower,
        .upperbound = upper,
    };
  };
};

vector<int> extractNumbers(string s, string delim);

int part1(vector<Race> races);

int main() {

  std::ifstream inputFile("input.txt");
  // std::ifstream inputFile("sample.txt");

  if (!inputFile.is_open()) {
    printf("Error opening file\n");
    return 1;
  }

  vector<Race> races = {};

  string line;
  int i = 0;
  while (getline(inputFile, line)) {
    if (i == 0) {
      for (int time : extractNumbers(line, ":")) {
        races.push_back(Race{.time = time});
      }
    } else if (i == 1) {
      vector<int> ds = extractNumbers(line, ":");
      for (int j = 0; j < ds.size(); j++) {
        races[j].distance = ds[j];
      }
    }
    i++;
  }

  printf("Part1: %d\n", part1(races));

  return 0;
}

int part1(vector<Race> races) {
  int mul = 1;
  for (Race race : races) {
    Range winningRange = race.getWinningRange();
    int minW = ceil(winningRange.lowerbound);
    int maxW = floor(winningRange.upperbound);

    if (race.d(minW) == (double)race.distance) {
      minW++;
    }

    if (race.d(maxW) == (double)race.distance) {
      maxW--;
    }

    mul *= (maxW - minW + 1);
  }
  return mul;
}

vector<int> extractNumbers(string s, string delim) {
  s = s.substr(s.find(delim) + 1, s.length());

  vector<int> numbers = {};
  int digit = 0;
  for (char c : s) {
    if (c == ' ') {
      if (digit != 0) {
        numbers.push_back(digit);
      }
      digit = 0;
      continue;
    }

    digit = digit * 10 + (c - '0');
  }

  if (digit != 0) {
    numbers.push_back(digit);
  }

  return numbers;
}
