#include <bits/stdc++.h>
using namespace std;

class BacktrackingSolver
{
public:
    bool isSafe(int row, int col, vector<string> &board, int n)
    {
        // upper-left diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
            if (board[i][j] == 'Q')
                return false;

        // left side
        for (int j = col; j >= 0; j--)
            if (board[row][j] == 'Q')
                return false;

        // lower-left diagonal
        for (int i = row, j = col; i < n && j >= 0; i++, j--)
            if (board[i][j] == 'Q')
                return false;

        return true;
    }

    void solve(int col, vector<string> &board, vector<vector<string>> &ans, int n, int &count)
    {
        if (col == n)
        {
            ans.push_back(board);
            count++;
            return;
        }

        for (int row = 0; row < n; row++)
        {
            if (isSafe(row, col, board, n))
            {
                board[row][col] = 'Q';
                solve(col + 1, board, ans, n, count);
                board[row][col] = '.';
            }
        }
    }

    pair<vector<vector<string>>, int> solveNQueens(int n)
    {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));
        int count = 0;
        solve(0, board, ans, n, count);
        return {ans, count};
    }
};

class BranchBoundSolver
{
public:
    void solve(int col, vector<string> &board, vector<vector<string>> &ans,
               vector<bool> &leftRow, vector<bool> &upperDiag, vector<bool> &lowerDiag,
               int n, int &count)
    {
        if (col == n)
        {
            ans.push_back(board);
            count++;
            return;
        }

        for (int row = 0; row < n; row++)
        {
            if (!leftRow[row] && !lowerDiag[row + col] && !upperDiag[n - 1 + col - row])
            {
                board[row][col] = 'Q';
                leftRow[row] = lowerDiag[row + col] = upperDiag[n - 1 + col - row] = true;

                solve(col + 1, board, ans, leftRow, upperDiag, lowerDiag, n, count);

                board[row][col] = '.';
                leftRow[row] = lowerDiag[row + col] = upperDiag[n - 1 + col - row] = false;
            }
        }
    }

    pair<vector<vector<string>>, int> solveNQueens(int n)
    {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));
        vector<bool> leftRow(n, false), upperDiag(2 * n - 1, false), lowerDiag(2 * n - 1, false);
        int count = 0;
        solve(0, board, ans, leftRow, upperDiag, lowerDiag, n, count);
        return {ans, count};
    }
};

int main()
{
    int n = 8;

    cout << "== Backtracking Solution ==\n";
    BacktrackingSolver btSolver;
    vector<vector<string>> btAns = btSolver.solveNQueens(n).first;
    int btCount = btSolver.solveNQueens(n).second;
    for (int i = 0; i < btAns.size(); ++i)
    {
        cout << "Arrangement " << i + 1 << ":\n";
        for (auto row : btAns[i])
            cout << row << endl;
        cout << endl;
    }
    cout << "Total Solutions (Backtracking): " << btCount << "\n\n";

    cout << "== Branch and Bound Solution ==\n";
    BranchBoundSolver bbSolver;
    vector<vector<string>> bbAns = bbSolver.solveNQueens(n).first;
    int bbCount = btSolver.solveNQueens(n).second;
    for (int i = 0; i < bbAns.size(); ++i)
    {
        cout << "Arrangement " << i + 1 << ":\n";
        for (auto row : bbAns[i])
            cout << row << endl;
        cout << endl;
    }
    cout << "Total Solutions (Branch and Bound): " << bbCount << "\n";

    return 0;
}
