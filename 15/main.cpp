#include <algorithm>
#include <cstdio>
#include <fstream>
#include <vector>

using namespace std;

int hasher(vector<char> &seq);
int part1(vector<vector<char>> &sequence);

enum Operation {
  ASSIGN = 0,
  REMOVE = 1,
};

struct SequenceEntry {
  vector<char> instructions;
  Operation op;
  int focalLength;
  int hash;

  static SequenceEntry parse(vector<char> &seq) {
    SequenceEntry entry;
    int pos = 0;
    while (seq[pos] != '=' && seq[pos] != '-') {
      entry.instructions.push_back(seq[pos]);
      pos++;
    }
    entry.op = seq[pos] == '=' ? ASSIGN : REMOVE;
    entry.focalLength = 0;
    if (entry.op == ASSIGN) {
      while (pos < seq.size() - 1) {
        pos++;
        entry.focalLength = entry.focalLength * 10 + (seq[pos] - '0');
      }
    }
    entry.hash = hasher(entry.instructions);
    return entry;
  }
};

int part2(vector<SequenceEntry> &sequence);

int main() {
  // ifstream file("sample");
  ifstream file("input");

  if (!file.is_open()) {
    printf("Could not open file\n");
    return 1;
  }

  vector<SequenceEntry> sequence2;

  vector<vector<char>> sequence;
  string line;

  vector<char> cur;
  while (getline(file, line)) {
    for (char c : line) {
      if (c != ',') {
        cur.push_back(c);
      } else {
        sequence.push_back(cur);
        sequence2.push_back(SequenceEntry::parse(cur));
        cur.clear();
      }
    }
  }
  if (!cur.empty()) {
    sequence.push_back(cur);
    sequence2.push_back(SequenceEntry::parse(cur));
  }

  printf("Part 1: %d\n", part1(sequence));
  printf("Part 2: %d\n", part2(sequence2));
}

int hasher(vector<char> &seq) {
  int hash = 0;
  for (char c : seq) {
    hash += c;
    hash *= 17;
    hash %= 256;
  }
  return hash;
}

int part2(vector<SequenceEntry> &sequence) {
  vector<SequenceEntry> boxes[256];

  for (SequenceEntry entry : sequence) {
    if (entry.op == ASSIGN) {
      vector<SequenceEntry> &s = boxes[entry.hash];
      bool add = true;
      for (SequenceEntry &e : s) {
        if (e.instructions == entry.instructions) {
          e.focalLength = entry.focalLength;
          add = false;
          break;
        }
      }
      if (add) {
        s.push_back(entry);
      }
    } else {
      vector<SequenceEntry> &v = boxes[entry.hash];
      v.erase(remove_if(v.begin(), v.end(),
                        [&entry](SequenceEntry &e) {
                          return e.instructions == entry.instructions;
                        }),
              v.end());
    }
  }

  int sum = 0;
  for (int pos = 0; pos < 256; pos++) {
    for (int innerPos = 0; innerPos < boxes[pos].size(); innerPos++) {
      sum += (pos + 1) * (innerPos + 1) * boxes[pos][innerPos].focalLength;
    }
  }
  return sum;
}

int part1(vector<vector<char>> &sequence) {
  int sum = 0;
  for (vector<char> seq : sequence) {
    sum += hasher(seq);
  }
  return sum;
}
