#include <bits/stdc++.h>

using namespace std;

string input1, input2;
vector<pair<int, int>> rules;
vector<vector<int>> updates;


int part1() {
  int count = 0;
  for (const auto &update : updates) {
    bool valid = true;

    for (const auto &rule : rules) {
      int left  = rule.first;
      int right = rule.second;

      auto it1 = find(update.begin(), update.end(), left);
      auto it2 = find(update.begin(), update.end(), right);

      if (it1 == update.end() || it2 == update.end()) {
        continue;
      }
      int index1 = distance(update.begin(), it1);
      int index2 = distance(update.begin(), it2);

      if (index1 > index2) {
        valid = false;
        break;
      }
    }
    if (valid) count += update[update.size() / 2];
  }

  return count;
}

int part2() {
  int count = 0;

  for (auto &update : updates) {
    bool valid = true;
    bool found = false;

    while (!found) {
      found = true;

      for (const auto &rule : rules) {
        int left  = rule.first;
        int right = rule.second;

        auto it1 = find(update.begin(), update.end(), left);
        auto it2 = find(update.begin(), update.end(), right);

        if (it1 == update.end() || it2 == update.end()) {
          continue;
        }
        int index1 = distance(update.begin(), it1);
        int index2 = distance(update.begin(), it2);

        if (index1 > index2) {
          swap(update[index1], update[index2]);
          valid = false;
          found = false;
          break;
        }
      }
    }
    if (!valid) count += update[update.size() / 2];
  }


  return count;
}

int main() {

  string input = "";

  char c;
  while (scanf("%c", &c) != EOF) {
    input += c;
  }

  int first = input.find("\n\n");
  input1    = input.substr(0, first);
  input2    = input.substr(first + 2);


  istringstream ss(input1);
  string line;
  while (getline(ss, line)) {
    int a, b;
    sscanf(line.c_str(), "%d|%d", &a, &b);
    rules.push_back({ a, b });
  }

  ss = istringstream(input2);
  while (getline(ss, line)) {
    vector<int> update;
    istringstream ss2(line);
    while (getline(ss2, line, ',')) {
      update.push_back(stoi(line));
    }
    updates.push_back(update);
  }


  cout << "Part 1: " << part1() << endl;
  cout << "Part 2: " << part2() << endl;

  return 0;
}