#include <iostream>
#include <cmath>
using namespace std;

bool canPlace(int mat[9][9], int i, int j, int n, int number) {
    //check for row and col
    for(int x = 0; x < n; x++) {
        if(mat[x][j] == number || mat[i][x] == number) {
            return false;
        }
    }
    //check for subgrid
    int rn = sqrt(n);
    int sx = (i/rn) * rn;
    int sy = (j/rn) * rn;
    for(int x = sx; x < sx + rn; x++) {
        for(int y = sy; y < sy + rn; y++) {
            if(mat[x][y] == number) {
                return false;
            }
        }
    }
    return true;

}
void print(int mat[9][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}
bool sudokuSolver(int mat[9][9], int i, int j, int n){
    //base case
    if(i == n) {
        return true;
    }
    //if row ends
    if(j == n) {
        return sudokuSolver(mat, i + 1, 0, n);
    }
    //skipping the cells which are already filled
    if(mat[i][j] != 0) {
        return sudokuSolver(mat, i, j + 1, n);
    }
    //rec case
    for(int number = 1; number <= 9; number++) {
        if(canPlace(mat, i, j, n, number)) {
            mat[i][j] = number;
            bool couldWeSolve = sudokuSolver(mat, i, j + 1, n);
            if(couldWeSolve) {
                return true;
            }
        }
    }
    //backtracking
    mat[i][j] = 0;
    return false;
}
int main() {
    int mat[9][9] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                       { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                       { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
    if(sudokuSolver(mat, 0, 0, 9))  {
        print(mat);
    }
}
