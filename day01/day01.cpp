#include <bits/stdc++.h>

using namespace std;

static vector<int> vec1, vec2;
#define INPUT_SIZE 1000

int part1() {
  sort(vec1.begin(), vec1.end());
  sort(vec2.begin(), vec2.end());

  int total = 0;
  for (size_t i = 0; i < INPUT_SIZE; i++) {
    printf("vec1[%ld]: %d vec2[%ld]: %d\n", i, vec1[i], i, vec2[i]);
    total += abs(vec1[i] - vec2[i]);
  }
  return total;
}

int part2() {
  unordered_map<int, int> map;
  map.reserve(INPUT_SIZE);
  int similarity = 0;

  for (const auto n : vec1) {
    if (!map.count(n)) {
      int count = 0, removed = 0;
      for (size_t i = 0; i < (size_t)INPUT_SIZE - removed; i++) {
        if (vec2[i] == n) {
          vec2.erase(vec2.begin() + i--);
          count++;
          removed++;
        }
      }
      map[n] = count;
      similarity += n * count;
    }
  }


  return similarity;
}

int main() {
  vec1.resize(INPUT_SIZE), vec2.resize(INPUT_SIZE);

  int num1, num2, i = 0;
  while (scanf("%d   %d", &num1, &num2) && i < INPUT_SIZE) {
    vec1[i] = num1;
    vec2[i] = num2;
    i++;
  }

  // int total = part1();
  // cout << "Total distance: " << total << endl;

  int similarity = part2();
  cout << "Similarity score: " << similarity << endl;

  return 0;
}