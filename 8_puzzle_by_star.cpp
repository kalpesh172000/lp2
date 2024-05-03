#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void findZero(vector<vector<int>> board, int &x, int &y){
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board.size(); j++){
            if (board[i][j] == 0){
                x = i;
                y = j;
                return;
            }
        }
    }
}

void printBoard(vector<vector<int>> board){
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board.size(); j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isGoalState(vector<vector<int> > &board, vector<vector<int> > &goal) {
     return board == goal;
}

int findMisplacedTiles(vector<vector<int>> &board, vector<vector<int> > &goal){
    int count = 0;

    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board.size(); j++){
            if (board[i][j] != goal[i][j])
                count++;
        }
    }

    return count;
}

void aStar(vector<vector<int>> &board, vector<vector<int>> &goal, int depth, int x, int y){
    //first  //second
    priority_queue<pair<int, vector<vector<int> > >, 
    vector<pair<int, vector<vector<int> > > >,
    greater<pair<int, vector<vector<int> > > > > pq;

    int g = depth;
    int h = findMisplacedTiles(board, goal);

    //g -> actual cost -> depth -> 0
    //h -> huristic value -> misplaced counter ->
    pq.push({(g + h), board});

    int parentX = -1, parentY = 
    while (!pq.empty()){
        vector<vector<int>> curr = pq.top().second;
        //vector<vector<int>> curr 
        pq.pop();
        printBoard(curr);

        int x, y;
        findZero(curr, x, y);

        if(isGoalState(curr, goal)){
            cout << "Goal State Reached" << endl;
            return;
        }

        int dx[] = {0, 0, -1, 1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; i++){
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < curr.size() && newY >= 0 && newY < curr.size()){
                swap(curr[x][y], curr[newX][newY]);             //swap 
                g = depth + 1;                                  //increment by 1  -> 1
                h = findMisplacedTiles(curr, goal);             //imp thing -> calculate huristic -> 2,3,7
                pq.push({(g + h), curr});                       //f(n) -> sorted by pq
                swap(curr[x][y], curr[newX][newY]);             //swap in another direction
            }
        }
    }

    return;
}

int main() {
    //definig the initial state
    // 0 -> blank space -> move this

    vector<vector<int>> initial = {
        {2, 8, 3},
        {1, 0, 4},
        {7, 6, 5}
    };

    //goal state
    vector<vector<int>> goal = {
        {0, 1, 4},
        {8, 6, 3},
        {5, 2, 7}
    };

    int x, y;

    //finding the empty box -> find black space -> put co-ordinate of blanck space in x y -> x=2,y=1
    findZero(initial, x, y);


    aStar(initial, goal, 0, x, y);

    return 0;
}


/*
Test cases:
Here are some possible test cases for the 8-puzzle problem with the given initial and goal states:

Initial state equal to goal state:
Initial:
Copy code
{0, 1, 2},
{3, 4, 5},
{6, 7, 8}
Goal:
Copy code
{0, 1, 2},
{3, 4, 5},
{6, 7, 8}
Expected output: Solution found in 0 moves.
Solvable puzzle with a few moves:
Initial:
Copy code
{1, 2, 5},
{3, 4, 8},
{6, 0, 7}
Goal:
Copy code
{1, 2, 5},
{3, 4, 8},
{6, 7, 0}
Expected output: Solution found in X moves (X > 0).
Unsolvable puzzle:
Initial:
Copy code
{1, 2, 3},
{4, 5, 6},
{8, 7, 0}
Goal:
Copy code
{1, 2, 3},
{4, 5, 6},
{7, 8, 0}
Expected output: No solution found.
Initial state already at goal state with some tiles misplaced:
Initial:
Copy code
{0, 1, 2},
{3, 5, 4},
{6, 7, 8}
Goal:
Copy code
{0, 1, 2},
{3, 4, 5},
{6, 7, 8}
Expected output: Solution found in X moves (X > 0).
Initial state completely reversed:
Initial:
Copy code
{8, 7, 6},
{5, 4, 3},
{2, 1, 0}
Goal:
Copy code
{0, 1, 2},
{3, 4, 5},
{6, 7, 8}
Expected output: Solution found in X moves (X > 0).
These test cases cover scenarios such as a solved puzzle, solvable puzzles with different complexities, unsolvable puzzles, and puzzles where the initial state is already close to the goal state.
*/