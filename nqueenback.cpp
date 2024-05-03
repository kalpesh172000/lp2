#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col, int N) {
    // Check for queens in the same column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check for queens in the upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) { //-----------------------check working for i-- j--
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check for queens in the upper right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

bool solveNQueensUtil(vector<vector<int>>& board, int row, int N) {
    if (row == N) {
        // All queens are placed successfully
        return true;
    }

    for (int col = 0; col < N; col++) { //-----------------------check working for col++ 
        if (isSafe(board, row, col, N)) {
            // Place queen on this position
            board[row][col] = 1;
            // Recur for the next row
            if (solveNQueensUtil(board, row + 1, N)) {
                return true;
            }
            // Backtrack and remove the queen from this position
            board[row][col] = 0;
        }
    }

    // Queen cannot be placed in any column in this row
    return false;
}

void solveNQueens(int N) {
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (solveNQueensUtil(board, 0, N)) {
        // Print the solution
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Solution does not exist." << endl;
    }
}

int main() {
    int N;
    cout << "Enter the number of queens (N): ";
    cin >> N;

    solveNQueens(N);

    return 0;
}
