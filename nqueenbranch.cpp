#include <iostream>
#include <vector>

using namespace std;

bool isSafe(int row,int col, vector<bool>& cols, int N, vector<bool>& leftdiagonal,vector<bool>& rightdiagonal) {

    if(cols[col]==true || leftdiagonal[row-col+N-1]== true || rightdiagonal[row+col]==true)
        return false;
    return true;
}

void printBoard(const vector<vector<int>>& board) {
    int N = board.size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool solveNQueensUtil(vector<vector<int>>& board, int row,vector<bool>& cols, int N,vector<bool>& leftdiagonal,vector<bool>& rightdiagonal) {
    if (row == N) {
        return true;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col,cols,N, leftdiagonal,rightdiagonal)) {
            // Place queen on this position
            board[row][col] = 1;
            cols[col] = true;
            leftdiagonal[row-col+N-1] = true;
            rightdiagonal[row+col] = true;

            // Recur for the next row
            if(solveNQueensUtil(board, row + 1,cols, N, leftdiagonal, rightdiagonal))
            {
                return true;
            }
            // Backtrack and remove the queen from this position
            board[row][col] = 0;
            cols[col] = false;
            leftdiagonal[row-col+N-1] = false;
            rightdiagonal[row+col] = false; }
    }
    return false;
}

void solveNQueens(int N) {
    vector<vector<int>> board(N, vector<int>(N, 0)); //--------remember this 
    vector<bool> cols(N, false); //--------remember this
    vector<bool> leftdiagonal(2*N-1,false);
    vector<bool> rightdiagonal(2*N-1,false);
    solveNQueensUtil(board, 0,cols, N,leftdiagonal,rightdiagonal);
    printBoard(board);
}

int main() {
    int N;
    cout << "Enter the number of queens (N): ";
    cin >> N;
    solveNQueens(N);
    return 0;
}
