#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <vector>

using std::string;
using std::vector;

struct Card {
  int number;
  vector<int> winningNumbers;
  vector<int> numbers;

  int amountWinningNumbers() {
    int amount = 0;
    for (int number : numbers) {
      if (std::find(winningNumbers.begin(), winningNumbers.end(), number) !=
          winningNumbers.end()) {
        amount++;
      }
    }
    return amount;
  }
};

vector<int> extractNumbers(string s, string delimiter);
int part1(vector<Card> cards);
int part2(vector<Card> cards);

int main() {
  std ::ifstream inputFile("input.txt");
  // std ::ifstream inputFile("sample.txt");
  if (!inputFile.is_open()) {
    printf("Error opening the file!\n");
    return 1;
  };

  vector<Card> cards = {};

  string line;
  int number = 1;
  while (std::getline(inputFile, line)) {
    string numbers = line.substr(line.find(":"), line.length());
    int idx = numbers.find("|");
    string winningNumbersStr = numbers.substr(2, idx - 1);
    string numbersStr = numbers.substr(idx + 2, numbers.length());

    Card card = Card{
        .number = number,
        .winningNumbers = extractNumbers(winningNumbersStr, " "),
        .numbers = extractNumbers(numbersStr, " "),
    };
    cards.push_back(card);
    number++;
  }

  /*for (Card card : cards) {
    printf("\nCard: %d\nWinning numbers: ", card.number);
    for (int w : card.winningNumbers) {
      printf("%d,", w);
    }
    printf("\nOwn numbers: ");
    for (int o : card.numbers) {
      printf("%d,", o);
    }
  }*/

  int points = part1(cards);
  printf("Part1: %d\n", points);
  int points2 = part2(cards);
  printf("Part2: %d\n", points2);
}

int part2(vector<Card> cards) {
  vector<int> counts = {0};
  counts.resize(cards.size());

  int counter = 0;
  for (Card cur : cards) {
    int matches = cur.amountWinningNumbers();
    for (int i = cur.number; i < cur.number + matches; i++) {
      counts[i] = counts[i] + counts[cur.number - 1] + 1;
    }
    counter += counts[cur.number - 1] + 1;
  }

  return counter;
}

int part1(vector<Card> cards) {
  int sum = 0;
  for (Card card : cards) {
    int a = card.amountWinningNumbers();
    if (a > 0) {
      sum += pow(2, a - 1);
    }
    // printf("Card %d has %d points.\n", card.number, points);
  }
  return sum;
}

vector<int> extractNumbers(string s, string delimiter) {
  vector<int> numbers = {};

  int digit = 0;

  for (char c : s) {
    if (c == ' ' || c == '|') {
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
