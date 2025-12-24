#include "Pathfinder.h"
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

// constructor - find start and end positions
Pathfinder::Pathfinder(const std::vector<std::vector<char>>& inputGrid) {
    grid = inputGrid;
    rows = grid.size();
    cols = (rows > 0) ? grid[0].size() : 0;
    
    // Find start and end positions
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'S') {
                start = {i, j};
            } else if (grid[i][j] == 'E') {
                end = {i, j};
            }
        }
    }
}

// check if valid position
bool Pathfinder::isValid(int row, int col) const {
    return (row >= 0 && row < rows && col >= 0 && col < cols && grid[row][col] != '#');
}

// add wall
void Pathfinder::setWall(int row, int col) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        if (grid[row][col] != 'S' && grid[row][col] != 'E') {
            grid[row][col] = '#';
        }
    }
}

// backtrack to mark path
void Pathfinder::reconstructPath(const vector<vector<pair<int, int>>>& parent) {
    pair<int, int> curr = end;
    
    // go backwards from end to start
    while (curr != start) {
        curr = parent[curr.first][curr.second];
        if (curr != start && curr != end) {
            grid[curr.first][curr.second] = '*';
        }
    }
}

// BFS to find path
bool Pathfinder::findPath() {
    queue<pair<int, int>> q;
    
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    
    // track parents for path reconstruction
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
    
    // up, right, down, left
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    
    q.push(start);
    visited[start.first][start.second] = true;
    
    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        
        int r = curr.first;
        int c = curr.second;
        
        // found the end
        if (curr == end) {
            reconstructPath(parent);
            return true;
        }
        
        // check all 4 directions
        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i];
            int nc = c + dy[i];
            
            if (isValid(nr, nc) && !visited[nr][nc]) {
                visited[nr][nc] = true;
                parent[nr][nc] = curr;
                q.push({nr, nc});
            }
        }
    }
    
    return false;  // no path
}

// print the grid
void Pathfinder::displayGrid() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}
