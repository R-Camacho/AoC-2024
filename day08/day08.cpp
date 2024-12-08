#include <bits/stdc++.h>

using namespace std;

static vector<string> grid;
static int rows, cols;
static unordered_map<char, vector<pair<int, int>>> antenna_map;

bool isValid(int x, int y) {
  return x >= 0 && x < rows && y >= 0 && y < cols;
}

pair<int, int> getDistance(pair<int, int> a, pair<int, int> b) {
  return { abs(a.first - b.first), abs(a.second - b.second) };
}

int part1() {

  vector<pair<int, int>> antinodes; // a ideia era fazer com sets

  for (const auto &[key, value] : antenna_map) {
    for (size_t i = 0; i < value.size(); i++) {
      for (size_t j = i + 1; j < value.size(); j++) {
        pair<int, int> distance = getDistance(value[i], value[j]);
        int x = distance.first, y = distance.second;

        if (value[i].second < value[j].second) {

          if (value[i].second - y >= 0 && value[i].first - x >= 0) {
            if (count(antinodes.begin(), antinodes.end(), make_pair(value[i].first - x, value[i].second - y)) == 0) {
              antinodes.push_back({ value[i].first - x, value[i].second - y });
            }
          }
          if (value[j].second + y < cols && value[j].first + x < rows) {
            if (count(antinodes.begin(), antinodes.end(), make_pair(value[j].first + x, value[j].second + y)) == 0) {
              antinodes.push_back({ value[j].first + x, value[j].second + y });
            }
          }
        } else {
          if (value[i].second + y < cols && value[i].first - x >= 0) {

            if (count(antinodes.begin(), antinodes.end(), make_pair(value[i].first - x, value[i].second + y)) == 0) {
              antinodes.push_back({ value[i].first - x, value[i].second + y });
            }
          }
          if (value[j].second - y >= 0 && value[j].first + x < rows) {
            if (count(antinodes.begin(), antinodes.end(), make_pair(value[j].first + x, value[j].second - y)) == 0) {
              antinodes.push_back({ value[j].first + x, value[j].second - y });
            }
          }
        }
      }
    }
  }


  return antinodes.size();
}

int part2() {
  vector<pair<int, int>> antinodes;

  for (const auto &[key, value] : antenna_map) {
    for (size_t i = 0; i < value.size(); i++) {
      for (size_t j = i + 1; j < value.size(); j++) {
        // Add original antennas as antinodes
        if (count(antinodes.begin(), antinodes.end(), value[i]) == 0) {
          antinodes.push_back(value[i]);
        }
        if (count(antinodes.begin(), antinodes.end(), value[j]) == 0) {
          antinodes.push_back(value[j]);
        }

        pair<int, int> distance = getDistance(value[i], value[j]);
        int x = distance.first, y = distance.second;

        if (value[i].second < value[j].second) {
          // Top left
          int curr_x = x, curr_y = y;
          while (value[i].second - curr_y >= 0 && value[i].first - curr_x >= 0) {
            if (count(antinodes.begin(), antinodes.end(), make_pair(value[i].first - curr_x, value[i].second - curr_y)) == 0) {
              antinodes.push_back({ value[i].first - curr_x, value[i].second - curr_y });
            }
            curr_x += x;
            curr_y += y;
          }

          // Bot right
          curr_x = x;
          curr_y = y;
          while (value[j].second + curr_y < cols && value[j].first + curr_x < rows) {
            if (count(antinodes.begin(), antinodes.end(), make_pair(value[j].first + curr_x, value[j].second + curr_y)) == 0) {
              antinodes.push_back({ value[j].first + curr_x, value[j].second + curr_y });
            }
            curr_x += x;
            curr_y += y;
          }
        } else {
          // Top right
          int curr_x = x, curr_y = y;
          while (value[i].second + curr_y < cols && value[i].first - curr_x >= 0) {
            if (count(antinodes.begin(), antinodes.end(), make_pair(value[i].first - curr_x, value[i].second + curr_y)) == 0) {
              antinodes.push_back({ value[i].first - curr_x, value[i].second + curr_y });
            }
            curr_x += x;
            curr_y += y;
          }

          // Bot left
          curr_x = x;
          curr_y = y;
          while (value[j].second - curr_y >= 0 && value[j].first + curr_x < rows) {
            if (count(antinodes.begin(), antinodes.end(), make_pair(value[j].first + curr_x, value[j].second - curr_y)) == 0) {
              antinodes.push_back({ value[j].first + curr_x, value[j].second - curr_y });
            }
            curr_x += x;
            curr_y += y;
          }
        }
      }
    }
  }

  return antinodes.size();
}

int main() {

  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  rows = grid.size();
  cols = grid[0].size();

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == '.') continue;
      antenna_map[grid[i][j]].push_back({ i, j });
    }
  }
  // debug antenna_map
  // for (auto [key, value] : antenna_map) {
  //   cout << key << ": ";
  //   for (auto [x, y] : value) {
  //     cout << "(" << x << ", " << y << ") ";
  //   }
  //   cout << endl;
  // }


  cout << "Part 1: " << part1() << endl;
  cout << "Part 2: " << part2() << endl;
  return 0;
}