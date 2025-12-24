#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <utility>
#include <string>

using namespace std;

class Pathfinder {
private:
    vector<vector<char>> grid;
    int rows;
    int cols;
    pair<int, int> start;
    pair<int, int> end;

    // check if position is valid
    bool isValid(int row, int col) const;
    
    // reconstruct path from parents
    void reconstructPath(const vector<vector<pair<int, int>>>& parent);

public:
    // constructor
    Pathfinder(const vector<vector<char>>& inputGrid);
    
    // set wall at position
    void setWall(int row, int col);
    
    // find shortest path with BFS
    bool findPath();
    
    // print grid
    void displayGrid() const;
    
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

#endif
