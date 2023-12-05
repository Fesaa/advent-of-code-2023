#include <cstdio>
#include <fstream>
#include <limits>
#include <vector>

using std::string;
using std::vector;

vector<long> extractNumbers(string s, string delimiter);

struct RangeConv {
  long source_start;
  long dest_start;
  long range;

  long map(long source) {
    if (source < source_start || source > source_start + range) {
      return source;
    }

    long diff = source - source_start;
    return dest_start + diff;
  }
};

struct Mapper {
  vector<RangeConv> convertors = {};

  void addRangeConv(RangeConv range) { convertors.push_back(range); }

  long map(long source) {
    long res = source;
    for (RangeConv conv : convertors) {
      res = conv.map(source);
      if (res != source) {
        return res;
      }
    }
    return source;
  }
};

long part1(vector<long> seeds, vector<Mapper *> mappers);

int main() {
  std ::ifstream inputFile("input.txt");
  // std ::ifstream inputFile("sample.txt");
  if (!inputFile.is_open()) {
    printf("Error opening the file!\n");
    return 1;
  };

  vector<long> seeds = {};
  vector<Mapper *> mappers = {};

  string line;
  long i = 0;
  Mapper *cur = NULL;
  while (getline(inputFile, line)) {
    if (i == 0) {
      string seedStr = line.substr(line.find(":") + 2, line.length());
      seeds = extractNumbers(seedStr, " ");
      i++;
      continue;
    }

    if (line.length() == 0) {
      if (cur != NULL) {
        mappers.push_back(cur);
      }
      cur = NULL;
      continue;
    }

    if (line.find(":") != string::npos) {
      cur = new Mapper{};
      continue;
    }

    // Line of numbers => RangeConv
    vector<long> numbers = extractNumbers(line, " ");
    RangeConv conv = RangeConv{
        .source_start = numbers[1],
        .dest_start = numbers[0],
        .range = numbers[2],
    };
    cur->addRangeConv(conv);
  }

  if (cur != NULL) {
    mappers.push_back(cur);
  }

  printf("Min seed: %ld\n", part1(seeds, mappers));

  return 0;
}

long part1(vector<long> seeds, vector<Mapper *> mappers) {
  long minMap = std::numeric_limits<long>::max();
  for (long seed : seeds) {
    long org = seed;
    for (Mapper *map : mappers) {
      seed = map->map(seed);
    }
    minMap = std::min(minMap, seed);
  }
  return minMap;
}

vector<long> extractNumbers(string s, string delimiter) {
  vector<long> numbers = {};

  long *digit = NULL;

  for (char c : s) {
    if (c == ' ') {
      if (digit != NULL) {
        numbers.push_back(*digit);
      }
      digit = NULL;
      continue;
    }
    if (digit == NULL) {
      long tmp = (c - '0');
      digit = &tmp;
    } else {
      long tmp = *digit * 10 + (c - '0');
      digit = &tmp;
    }
  }
  if (digit != NULL) {
    numbers.push_back(*digit);
  }

  return numbers;
}
