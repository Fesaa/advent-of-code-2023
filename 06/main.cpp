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
  long time;
  long distance;

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

vector<long> extractNumbers(string s, string delim, bool resetOnSpace);

long part1(vector<Race> races);

long part2(Race race);

int main() {

  std::ifstream inputFile("input.txt");
  // std::ifstream inputFile("sample.txt");

  if (!inputFile.is_open()) {
    printf("Error opening file\n");
    return 1;
  }

  vector<Race> races = {};
  Race fullRace;

  string line;
  long i = 0;
  while (getline(inputFile, line)) {
    if (i == 0) {
      for (long time : extractNumbers(line, ":", true)) {
        races.push_back(Race{.time = time});
      }
      fullRace = Race{.time = extractNumbers(line, ":", false)[0]};
    } else if (i == 1) {
      vector<long> ds = extractNumbers(line, ":", true);
      for (long j = 0; j < ds.size(); j++) {
        races[j].distance = ds[j];
      }
      fullRace.distance = extractNumbers(line, ":", false)[0];
    }
    i++;
  }

  printf("Part1: %ld\n", part1(races));
  printf("Part2: %ld\n", part2(fullRace));

  return 0;
}

long part2(Race race) { return part1({race}); }

long part1(vector<Race> races) {
  long mul = 1;
  for (Race race : races) {
    Range winningRange = race.getWinningRange();
    long minW = ceil(winningRange.lowerbound);
    long maxW = floor(winningRange.upperbound);

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

vector<long> extractNumbers(string s, string delim, bool resetOnSpace) {
  s = s.substr(s.find(delim) + 1, s.length());

  vector<long> numbers = {};
  long digit = 0;
  for (char c : s) {
    if (c == ' ') {
      if (digit != 0 && resetOnSpace) {
        numbers.push_back(digit);
      }
      if (resetOnSpace) {
        digit = 0;
      }
      continue;
    } else {
      digit = digit * 10 + (c - '0');
    }
  }

  if (digit != 0) {
    numbers.push_back(digit);
  }

  return numbers;
}
