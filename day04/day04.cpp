#include <bits/stdc++.h>

using namespace std;

static vector<string> lines;
static int rows;
static int cols;

static const vector<pair<int, int>> directions = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }, { 1, 1 }, { -1, -1 },
  { 1, -1 }, { -1, 1 } };

static const vector<pair<int, int>> diagonals = { { 1, 1 }, { -1, -1 }, { 1, -1 }, { -1, 1 } };

inline bool isValid(int x, int y) {
  return 0 <= x && x < rows && 0 <= y && y < cols;
}

inline bool isBorder(int x, int y) {
  return x == 0 || x == rows - 1 || y == 0 || y == cols - 1;
}

bool searchWord(int x, int y, int dx, int dy) {
  const string word = "XMAS";
  const int wordLen = word.length();
  for (int i = 0; i < wordLen; i++) {
    const int newx = x + i * dx;
    const int newy = y + i * dy;
    if (!isValid(newx, newy) || lines[newx][newy] != word[i]) {
      return false;
    }
  }
  return true;
}

int canForm(int x, int y) {
  if (isBorder(x, y)) return 0;

  string diag1 = "", diag2 = "";
  const string word = "MAS";
  const int wordLen = word.length();


  for (int i = -1; i < wordLen - 1; i++) {
    diag1 += lines[x + i][y + i];
    diag2 += lines[x + i][y - i];
  }

  int count = 0;
  if (diag1 == word) count++;
  if (diag2 == word) count++;

  if (string(diag1.rbegin(), diag1.rend()) == word) count++;
  if (string(diag2.rbegin(), diag2.rend()) == word) count++;

  return count;
}

int part1() {

  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (const auto &direction : directions) {
        count += searchWord(i, j, direction.first, direction.second);
      }
    }
  }

  return count;
}

int part2() {

  const int rows = lines.size();
  const int cols = lines[0].size();

  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (lines[i][j] == 'A') count += canForm(i, j) == 2;
    }
  }
  return count;
}

int main() {

  ifstream file("day04/input.txt");
  string line;
  while (getline(file, line)) {
    lines.push_back(line);
  }

  rows = lines.size();
  cols = lines[0].size();

  cout << "Part 1: " << part1() << endl;

  cout << "Part 2: " << part2() << endl;

  return 0;
}