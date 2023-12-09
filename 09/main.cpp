#include <cstdio>
#include <fstream>
#include <vector>

using std::string;
using std::vector;

struct Reading {
  bool final;
  bool solved;
  Reading *diff;
  int depth;

  void setDepth(int d) { depth = d; }

  Reading make_diff() {
    Reading inner;
    inner.depth = depth + 1;
    inner.final = true;
    inner.solved = false;
    inner.diff = NULL;
    for (int pos = 1; pos < readings.size(); pos++) {
      inner.add_reading(readings[pos] - readings[pos - 1]);
    }
    return inner;
  }

  long solve() {
    if (final) {
      return 0;
    }
    if (solved) {
      return readings[readings.size() - 1];
    }
    Reading next = make_diff();
    diff = &next;

    long s = diff->solve();
    long cnt = readings[readings.size() - 1] + s;
    readings.push_back(cnt);
    solved = true;
    return cnt;
  }

  long solveFirst() {
    if (final) {
      return 0;
    }
    if (solved) {
      return readings[0];
    }
    Reading next = make_diff();
    diff = &next;

    long s = diff->solveFirst();
    long cnt = readings[0] - s;
    readings.insert(readings.begin(), cnt);
    solved = true;
    return cnt;
  }

  void dumb() {
    printf("Reading(");
    for (long i : readings) {
      printf(" %ld,", i);
    }
    printf(")");
  }

  void add_reading(long r) {
    readings.push_back(r);
    final = final && r == 0;
  }

private:
  vector<long> readings;
};

Reading extractReading(string line);

Reading makeDefault() {
  Reading r;
  r.depth = 0;
  r.solved = false;
  r.final = true;
  r.diff = NULL;
  return r;
}

long part1(vector<Reading> readings) {
  long sum = 0;
  for (Reading r : readings) {
    long s = r.solve();
    sum += s;
  }
  return sum;
}

long part2(vector<Reading> readings) {
  long sum = 0;
  for (Reading r : readings) {
    long s = r.solveFirst();
    sum += s;
  }
  return sum;
}

int main() {
  // std::ifstream file("sample.txt");
  std::ifstream file("input.txt");
  if (!file.is_open()) {
    printf("Could not open file\n");
    return 1;
  }

  vector<Reading> readings;

  string line;
  while (std::getline(file, line)) {
    readings.push_back(extractReading(line));
  }

  printf("Part1: %ld\n", part1(readings));
  printf("Part2: %ld\n", part2(readings));

  return 0;
}

Reading extractReading(string line) {
  Reading reading = makeDefault();

  long digit = 0;
  int neg = 1;
  bool num = false;
  for (char c : line) {
    if (c == '-') {
      neg = -1;
    } else if (c == ' ') {
      if (num) {
        reading.add_reading(neg * digit);
      }
      digit = 0;
      neg = 1;
      num = false;
    } else {
      digit = digit * 10 + (c - '0');
      num = true;
    }
  }

  if (num) {
    reading.add_reading(neg * digit);
  }

  return reading;
}
