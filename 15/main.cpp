#include <cstdio>
#include <fstream>
#include <vector>

using namespace std;

int hasher(vector<char> &seq);
int part1(vector<vector<char>> &sequence);

int main() {
  // ifstream file("sample");
  ifstream file("input");

  if (!file.is_open()) {
    printf("Could not open file\n");
    return 1;
  }

  vector<vector<char>> sequence;
  string line;

  vector<char> cur;
  while (getline(file, line)) {
    for (char c : line) {
      if (c != ',') {
        cur.push_back(c);
      } else {
        sequence.push_back(cur);
        cur.clear();
      }
    }
  }
  if (!cur.empty()) {
    sequence.push_back(cur);
  }

  printf("Part 1: %d\n", part1(sequence));
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

int part1(vector<vector<char>> &sequence) {
  int sum = 0;
  for (vector<char> seq : sequence) {
    sum += hasher(seq);
  }
  return sum;
}
