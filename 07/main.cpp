#include <algorithm>
#include <cstdio>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

struct Card {
  char _char;
  int worth;

  bool operator<(const Card &other) { return worth < other.worth; }
  bool operator==(const Card &other) { return worth == other.worth; }
};

struct Hand {
  vector<Card> cards;
  int bid;

  int type;

  void setType() {
    map<char, int> occurances;
    for (Card card : cards) {
      if (occurances.count(card._char) == 0) {
        occurances[card._char] = 1;
      } else {
        occurances[card._char] = occurances[card._char] + 1;
      }
    }

    int t = 0;
    for (const auto &pair : occurances) {
      t = std::max(t, pair.second);
    }

    // Five of a kind
    if (t == 5) {
      type = 6;
      return;
    }

    // Four of a kind
    if (t == 4) {
      type = 5;
      return;
    }

    if (t == 3) {
      // Full house
      if (occurances.size() == 2) {
        type = 4;
        return;
      }
      // Three of a kind
      type = 3;
      return;
    }

    if (t == 2) {
      // Two pair
      if (occurances.size() == 3) {
        type = 2;
        return;
      }
      // One pair
      type = 1;
      return;
    }

    // High card
    type = 0;
  }

  bool operator<(Hand &other) {
    if (type == other.type) {
      for (int pos = 0; pos < cards.size(); pos++) {
        if (cards[pos] == other.cards[pos]) {
          continue;
        }
        return cards[pos] < other.cards[pos];
      }
    }
    return type < other.type;
  }
};

Hand fromString(string cards, string bid);

int part1(vector<Hand> hands);

int main() {

  // std::fstream inputFile("sample.txt");
  std::fstream inputFile("input.txt");

  if (!inputFile.is_open()) {
    printf("Could not open file. \n");
    return 1;
  }

  vector<Hand> hands;
  string line;
  while (std::getline(inputFile, line)) {
    string cards = line.substr(0, line.find(" "));
    string bid = line.substr(line.find(" ") + 1, line.length());
    hands.push_back(fromString(cards, bid));
  }

  printf("Part1: %d\n", part1(hands));

  return 0;
}

int part1(vector<Hand> hands) {
  std::sort(hands.begin(), hands.end());

  int sum = 0;
  for (int pos = 0; pos < hands.size(); pos++) {
    sum += hands[pos].bid * (pos + 1);
  }

  return sum;
}

Hand fromString(string cards, string bid) {
  vector<Card> cardsV;
  for (char c : cards) {
    Card cur;
    switch (c) {
    case '2':
      cur = Card{._char = c, .worth = 0};
      break;
    case '3':
      cur = Card{._char = c, .worth = 1};
      break;
    case '4':
      cur = Card{._char = c, .worth = 2};
      break;
    case '5':
      cur = Card{._char = c, .worth = 3};
      break;
    case '6':
      cur = Card{._char = c, .worth = 4};
      break;
    case '7':
      cur = Card{._char = c, .worth = 5};
      break;
    case '8':
      cur = Card{._char = c, .worth = 6};
      break;
    case '9':
      cur = Card{._char = c, .worth = 7};
      break;
    case 'T':
      cur = Card{._char = c, .worth = 8};
      break;
    case 'J':
      cur = Card{._char = c, .worth = 9};
      break;
    case 'Q':
      cur = Card{._char = c, .worth = 10};
      break;
    case 'K':
      cur = Card{._char = c, .worth = 11};
      break;
    case 'A':
      cur = Card{._char = c, .worth = 12};
      break;
    }
    cardsV.push_back(cur);
  }

  int d = 0;
  for (char c : bid) {
    d = d * 10 + (c - '0');
  }

  Hand h = Hand{.cards = cardsV, .bid = d};
  h.setType();
  return h;
}
