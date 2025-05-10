#include <bits/stdc++.h>
using namespace std;

void printBoard(vector<int> &board, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i] == j)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafeBacktracking(vector<int> &board, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
        {
            return false;
        }
    }
    return true;
}

void solveNQueensBacktracking(vector<int> &board, int row, int n, int &solutions)
{
    if (row == n)
    {
        printBoard(board, n);
        solutions++;
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (isSafeBacktracking(board, row, col))
        {
            board[row] = col;
            solveNQueensBacktracking(board, row + 1, n, solutions);
            board[row] = -1;
        }
    }
}

void solveNQueensUsingBacktracking(int n)
{
    int solutions = 0;
    vector<int> board(n, -1);
    solveNQueensBacktracking(board, 0, n, solutions);

    if (solutions == 0)
    {
        cout << "Solution does not exist!" << endl;
    }
    else
    {
        cout << "Total number of solutions: " << solutions << endl;
    }
}

bool isSafeBranchAndBound(vector<int> &board, int row, int col, int n)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
        {
            return false;
        }
    }
    return true;
}

void solveNQueensBranchAndBound(vector<int> &board, int row, int n, int &solutions)
{
    if (row == n)
    {
        printBoard(board, n);
        solutions++;
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (isSafeBranchAndBound(board, row, col, n))
        {
            board[row] = col;
            solveNQueensBranchAndBound(board, row + 1, n, solutions);
            board[row] = -1;
        }
    }
}

void solveNQueensUsingBranchAndBound(int n)
{
    vector<int> board(n, -1);
    int solutions = 0;
    solveNQueensBranchAndBound(board, 0, n, solutions);
    if (solutions == 0)
    {
        cout << "Solution does not exist!" << endl;
    }
    else
    {
        cout << "Total number of solutions: " << solutions << endl;
    }
}

int main()
{
    int choice, n;
    cout << "Enter the number of queens (n): ";
    cin >> n;

    cout << "1. Solve using Backtracking\n";
    cout << "2. Solve using Branch and Bound\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        solveNQueensUsingBacktracking(n);
        break;
    case 2:
        solveNQueensUsingBranchAndBound(n);
        break;
    default:
        cout << "Invalid choice!\n";
    }

    return 0;
}