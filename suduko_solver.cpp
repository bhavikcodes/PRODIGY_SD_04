#include <iostream>
using namespace std;

#define N 9 // Size of the Sudoku grid (9x9)

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number is not in the current row and column
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }
       // Check if the number is not in the current 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
return true;
}
// Backtracking function to solve the Sudoku
bool solveSudoku(int grid[N][N], int row, int col) {
    // If we have reached the last cell, the puzzle is solved
    if (row == N - 1 && col == N) {
        return true;
    }
    // Move to the next row if we reach the end of a column
    if (col == N) {
        row++;
        col = 0;
    }
    // Skip the cells that are already filled
    if (grid[row][col] != 0) {
        return solveSudoku(grid, row, col + 1);
    }
    // Try placing numbers 1 to 9 in the cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            // Place the number
            grid[row][col] = num;
       // Recur to check if this leads to a solution
            if (solveSudoku(grid, row, col + 1)) {
                return true;
            }
               // If it doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }
    return false;
}
int main() {
    int grid[N][N];
    // Input Sudoku puzzle from the user
    cout << "Enter the Sudoku grid (9x9) row by row. Use 0 for empty cells:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }
    cout << "Unsolved Sudoku puzzle:" << endl;
    printGrid(grid);
    if (solveSudoku(grid, 0, 0)) {
        cout << "\nSolved Sudoku puzzle:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle." << endl;
    }
    return 0;
}
