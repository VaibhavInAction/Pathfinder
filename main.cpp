#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Pathfinder.h"

using namespace std;

// read grid from file
vector<vector<char>> readGridFromFile(const string& filename, int& rows, int& cols) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file " << filename << endl;
        return {};
    }
    
    inFile >> rows >> cols;
    inFile.ignore();
    
    vector<vector<char>> grid(rows, vector<char>(cols));
    
    // read the grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char ch;
            inFile >> ch;
            grid[i][j] = ch;
        }
    }
    
    inFile.close();
    return grid;
}

// write output to file
void writeOutputToFile(const string& filename, const string& content) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Could not create output file " << filename << endl;
        return;
    }
    outFile << content;
    outFile.close();
}

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <test_case_file>" << endl;
        return 1;
    }
    
    string inputFile = argv[1];
    int rows, cols;
    
    vector<vector<char>> grid = readGridFromFile(inputFile, rows, cols);
    
    if (grid.empty()) {
        cerr << "Failed to read grid from file." << endl;
        return 1;
    }
    
    Pathfinder pathfinder(grid);
    
    cout << "Initial Grid:" << endl;
    pathfinder.displayGrid();
    cout << endl;
    
    bool pathFound = pathfinder.findPath();
    
    if (pathFound) {
        cout << "Path found! Grid with path marked:" << endl;
        pathfinder.displayGrid();
    } else {
        cout << "No path found from Start to End." << endl;
    }
    
    return 0;
}
