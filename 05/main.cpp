#include <cstdio>
#include <fstream>
#include <limits>
#include <queue>
#include <vector>

using std::queue;
using std::string;
using std::vector;

vector<long> extractNumbers(string s, string delimiter);

struct Range {
  long start;
  long end;
};

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

  long source_end() { return source_start + range; }
  long dest_end() { return dest_start + range; }
};

struct Mapper {
  vector<RangeConv> convertors = {};

  void addRangeConv(RangeConv range) { convertors.push_back(range); }

  vector<Range> map(Range range) {
    vector<Range> ranges = {};
    queue<Range> rangeQueue;
    rangeQueue.push(range);

    while (!rangeQueue.empty()) {
      Range cur = rangeQueue.front();
      int curSize = ranges.size();
      rangeQueue.pop();
      for (RangeConv conv : convertors) {
        // No overlap
        if (cur.end < conv.source_start || cur.start > conv.source_end()) {
          continue;
        }

        // Full overlap
        if (cur.start >= conv.source_start && cur.end <= conv.source_end()) {
          Range r =
              Range{.start = conv.map(cur.start), .end = conv.map(cur.end)};
          ranges.push_back(r);
          break;
        }

        // Partial overlap

        if (cur.start <= conv.source_start && cur.end >= conv.source_end()) {
          Range convSize =
              Range{.start = conv.dest_start, .end = conv.dest_end()};
          Range leftSize =
              Range{.start = cur.start, .end = conv.source_start - 1};
          Range rightSize =
              Range{.start = conv.source_end() + 1, .end = cur.end};
          ranges.push_back(convSize);
          rangeQueue.push(leftSize);
          rangeQueue.push(rightSize);
          break;
        }

        // End poking out
        if (cur.start >= conv.source_start) {
          Range overlap =
              Range{.start = conv.map(cur.start), .end = conv.dest_end()};
          Range pokingOut =
              Range{.start = conv.source_end() + 1, .end = cur.end};
          ranges.push_back(overlap);
          rangeQueue.push(pokingOut);
          break;
        }

        // Start poking out
        Range overlap =
            Range{.start = conv.dest_start, .end = conv.map(cur.end)};
        Range pokingOut =
            Range{.start = cur.start, .end = conv.source_start - 1};
        ranges.push_back(overlap);
        rangeQueue.push(pokingOut);
        break;
      }

      if (ranges.size() == curSize) {
        ranges.push_back(cur);
      }
    }

    return ranges;
  }

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
long part2(vector<long> seeds, vector<Mapper *> mappers);

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

  printf("part1: %ld\n", part1(seeds, mappers));
  printf("part2: %ld\n", part2(seeds, mappers));

  return 0;
}

long part2(vector<long> seeds, vector<Mapper *> mappers) {
  vector<Range> ranges;
  long last = 0;
  for (int i = 0; i < seeds.size(); i++) {
    if (i % 2 == 1) {
      ranges.push_back(Range{.start = last, .end = last + seeds[i]});
    } else {
      last = seeds[i];
    }
  }

  long minmap = std::numeric_limits<long>::max();
  for (Range range : ranges) {
    vector<Range> conv;
    conv.push_back(range);
    for (Mapper *map : mappers) {
      vector<Range> mapConv;
      for (Range cur : conv) {
        vector<Range> convCur = map->map(cur);
        mapConv.insert(mapConv.end(), convCur.begin(), convCur.end());
      }
      conv = mapConv;
    }
    for (Range r : conv) {
      minmap = std::min(minmap, r.start);
      minmap = std::min(minmap, r.end);
    }
  }

  return minmap;
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
