#include <bits/stdc++.h>

using namespace std;

int part1(string input) {
  int total = 0;

  while (input.length() > 5) {
    size_t idx = input.find("mul(");
    if (idx == string::npos) {
      break;
    }
    idx += 4;
    if (!isdigit(input[idx])) {
      input.erase(0, idx + 1);
      continue;
    }
    int num1 = 0;
    while (isdigit(input[idx])) {
      num1 = num1 * 10 + input[idx] - '0';
      idx++;
    }
    if (input[idx] != ',') {
      input.erase(0, idx);
      continue;
    }
    idx++;
    int num2 = 0;
    while (isdigit(input[idx])) {
      num2 = num2 * 10 + input[idx] - '0';
      idx++;
    }
    if (input[idx] != ')') {
      input.erase(0, idx);
      continue;
    }
    total += num1 * num2;
    input.erase(0, idx);
  }

  return total;
}

int part2(string input) {
  size_t dont_idx, do_idx;

  while ((dont_idx = input.find("don't()")) != string::npos) {
    do_idx = input.find("do()", dont_idx);
    if (do_idx != string::npos) {
      input.erase(dont_idx, do_idx - dont_idx + 4);
    } else {
      break;
    }
  }

  return part1(input);
}

int main() {
  string input = "", line;
  while (getline(cin, line)) {
    input += line;
  }

  int total1 = part1(input);
  cout << "Part 1: " << total1 << endl;

  int total2 = part2(input);
  cout << "Part 2: " << total2 << endl;
  return 0;
}