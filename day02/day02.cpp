#include <bits/stdc++.h>

using namespace std;

bool isLineSafe(string line) {
  istringstream iss(line);
  int num, i = 0;
  bool decreasing = false;
  bool increasing = false;
  int prev        = -1;
  while (iss >> num) {
    if (i == 0) {
      i++;
      prev = num;
      continue;
    }
    if (i == 1) {
      if (prev < num) increasing = true;
      if (prev > num) decreasing = true;
    }

    // not 1 <= abs(prev - num) <= 3
    if (1 > abs(prev - num) || abs(prev - num) > 3) return false;

    if (increasing && prev > num) return false;
    if (decreasing && prev < num) return false;

    prev = num;
    i++;
  }
  return true;
}


int part1() {
  int safe = 0;
  string line;
  while (getline(cin, line)) {
    istringstream iss(line);
    if (isLineSafe(line)) safe++;
  }
  return safe;
}

int part2() {
  int safe = 0;
  string line;
  while (getline(cin, line)) {
    istringstream iss(line);
    vector<int> nums(0);

    int num;
    while (iss >> num) {
      nums.push_back(num);
    }

    for (size_t i = 0; i < nums.size(); i++) {
      ostringstream newLineBuilder;
      size_t j = 0;
      while (j < nums.size()) {
        if (j != i) newLineBuilder << nums[j] << " ";
        j++;
      }

      // Get the resulting string and remove trailing space
      std::string newLine = newLineBuilder.str();
      if (!newLine.empty() && newLine.back() == ' ') {
        newLine.pop_back();
      }

      if (isLineSafe(newLine)) {
        safe++;
        break;
      }

      // Print the new line
      std::cout << newLine << std::endl;
    }
  }

  return safe;
}

int main() {
  // int safe1 = part1();
  // cout << "safe: " << safe1 << endl;

  int safe2 = part2();
  cout << "safe2: " << safe2 << endl;


  return 0;
}