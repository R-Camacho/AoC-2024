#include <bits/stdc++.h>

using namespace std;

vector<vector<uint64_t>> equations;


vector<uint64_t> recursive1(vector<uint64_t> past_results, vector<uint64_t> nums, uint64_t target) {
  vector<uint64_t> new_past_results;
  uint64_t nums0 = nums[0];
  for (const auto result : past_results) {
    if (result > target) {
      continue;
    }
    new_past_results.push_back(result * nums0);
    new_past_results.push_back(result + nums0);
  }
  if (nums.size() <= 1) return new_past_results;
  vector<uint64_t> new_nums = vector<uint64_t>(nums.begin() + 1, nums.end());
  return recursive1(new_past_results, new_nums, target);
}

vector<uint64_t> recursive2(vector<uint64_t> past_results, vector<uint64_t> nums, uint64_t target) {
  vector<uint64_t> new_past_results;
  uint64_t nums0 = nums[0];
  for (const auto result : past_results) {
    if (result > target) {
      continue;
    }
    new_past_results.push_back(result * nums0);
    new_past_results.push_back(result + nums0);

    new_past_results.push_back(static_cast<uint64_t>(stoll(to_string(result) + to_string(nums0))));
  }
  if (nums.size() <= 1) return new_past_results;
  vector<uint64_t> new_nums = vector<uint64_t>(nums.begin() + 1, nums.end());
  return recursive2(new_past_results, new_nums, target);
}


uint64_t part1() {
  uint64_t total = 0;

  for (const auto &eq : equations) {
    vector<uint64_t> all = recursive1({ eq[1] }, vector<uint64_t>(eq.begin() + 2, eq.end()), eq[0]);
    if (count(all.begin(), all.end(), eq[0])) total += eq[0];
  }

  return total;
}


uint64_t part2() {
  uint64_t total = 0;

  for (const auto &eq : equations) {
    vector<uint64_t> all = recursive2({ eq[1] }, vector<uint64_t>(eq.begin() + 2, eq.end()), eq[0]);
    if (count(all.begin(), all.end(), eq[0])) total += eq[0];
  }

  return total;
}

int main() {
  vector<string> input;
  string line;
  while (getline(cin, line)) {
    input.push_back(line);
  }
  for (const auto &line : input) {
    vector<uint64_t> v;
    istringstream iss(line);
    string s;

    while (iss >> s) {
      if (s.back() == ':') {
        v.push_back(stoll(s.substr(0, s.size() - 1)));
      } else {
        v.push_back(stoll(s));
      }
    }

    equations.push_back(v);
  }

  cout << "Part 1: " << part1() << endl;
  cout << "Part 2: " << part2() << endl;
  return 0;
}