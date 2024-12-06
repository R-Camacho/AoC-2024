#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> directions = {
  { -1, 0 }, // Up
  { 0, 1 },  // Right
  { 1, 0 },  // Down
  { 0, -1 }  // Left
};

unordered_map<char, int> direction_map = { { '^', 0 }, { '>', 1 }, { 'v', 2 }, { '<', 3 } };

static vector<string> grid;
static int rows, cols;
static int start_x, start_y, start_dir;

bool isValid(int x, int y) {
  return x >= 0 && x < rows && y >= 0 && y < cols;
}

int part1() {
  int x = start_x, y = start_y, dir = start_dir;
  set<pair<int, int>> visited;
  visited.insert({ x, y });

  while (true) {
    int next_x = x + directions[dir].first;
    int next_y = y + directions[dir].second;


    if (!isValid(next_x, next_y)) break;

    if (grid[next_x][next_y] == '#') {
      // 90 graus para a direita
      dir = (dir + 1) % 4;
    } else {
      x = next_x;
      y = next_y;
    }

    visited.insert({ x, y });
  }

  return visited.size();
}

int part2() {
  // brute force :(
  int count = 0;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {

      if ((i == start_x && j == start_y) || grid[i][j] == '#') continue;

      char original = grid[i][j];
      grid[i][j]    = '#'; // colocar um block neste ponto


      int x = start_x, y = start_y, dir = start_dir;
      bool stuck = false;
      unordered_map<string, bool> visited;
      // igual à parte 1
      while (1) {
        int next_x = x + directions[dir].first;
        int next_y = y + directions[dir].second;

        if (!isValid(next_x, next_y)) break;

        string key = to_string(x) + " " + to_string(y) + " " + to_string(dir);

        if (visited.count(key) && visited[key] == true) {
          stuck = true;
          break;
        }
        visited[key] = true;

        if (grid[next_x][next_y] == '#') {
          // 90 graus para a direita
          dir = (dir + 1) % 4;
        } else {
          x = next_x;
          y = next_y;
        }
      }
      count += stuck;

      grid[i][j] = original; // reset no ponto
    }
  }
  return count;
}


int main() {
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  rows       = grid.size();
  cols       = grid[0].size();
  bool found = false;
  for (int i = 0; i < rows && !found; i++) {
    for (int j = 0; j < cols; j++) {
      if (direction_map.find(grid[i][j]) != direction_map.end()) {
        start_x   = i;
        start_y   = j;
        start_dir = direction_map[grid[i][j]];
        found     = true;
        break;
      }
    }
  }

  cout << "Part 1: " << part1() << endl;
  cout << "Part 2: " << part2() << endl;
  return 0;
}