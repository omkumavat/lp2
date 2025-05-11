// #include <bits/stdc++.h>
// using namespace std;
// const int N = 3;

// struct PuzzleState
// {
//     int puzzle[N][N];
//     int zeroRow, zeroCol;
//     int g; 
//     int h; 

//     bool operator<(const PuzzleState &other) const
//     {
//         return (g + h) > (other.g + other.h); 
//     }
// };

// void printPuzzle(const PuzzleState &state)
// {
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             cout << state.puzzle[i][j] << " ";
//         }
//         cout << endl;
//     }
//     cout << "-----\n";
// }

// bool isEqual(const PuzzleState &a, const PuzzleState &b)
// {
//     for (int i = 0; i < N; i++)
//         for (int j = 0; j < N; j++)
//             if (a.puzzle[i][j] != b.puzzle[i][j])
//                 return false;
//     return true;
// }

// int calcManhattanDistance(const PuzzleState &state, const PuzzleState &goal)
// {
//     int dist = 0;
//     unordered_map<int, pair<int, int>> goalPos;
//     for (int i = 0; i < N; i++)
//         for (int j = 0; j < N; j++)
//             goalPos[goal.puzzle[i][j]] = {i, j};

//     for (int i = 0; i < N; i++)
//         for (int j = 0; j < N; j++)
//         {
//             int val = state.puzzle[i][j];
//             if (val != 0)
//             {
//                 int gi = goalPos[val].first;
//                 int gj = goalPos[val].second;
//                 dist += abs(i - gi) + abs(j - gj);
//             }
//         }
//     return dist;
// }

// bool isValid(int r, int c)
// {
//     return r >= 0 && r < N && c >= 0 && c < N;
// }

// vector<PuzzleState> generateNextStates(const PuzzleState &current, const PuzzleState &goal)
// {
//     vector<PuzzleState> nextStates;
//     const int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
//     int r = current.zeroRow, c = current.zeroCol;

//     for (int i = 0; i < 4; i++)
//     {
//         int nr = r + dr[i], nc = c + dc[i];
//         if (isValid(nr, nc))
//         {
//             PuzzleState next = current;
//             swap(next.puzzle[r][c], next.puzzle[nr][nc]);
//             next.zeroRow = nr;
//             next.zeroCol = nc;
//             next.g = current.g + 1;
//             next.h = calcManhattanDistance(next, goal);
//             nextStates.push_back(next);
//         }
//     }
//     return nextStates;
// }

// // New: unique string hash for each state
// string getHash(const PuzzleState &state)
// {
//     string key;
//     for (int i = 0; i < N; i++)
//         for (int j = 0; j < N; j++)
//             key += to_string(state.puzzle[i][j]) + ",";
//     return key;
// }

// bool isSolvableForBoth(const PuzzleState &initial, const PuzzleState &goal)
// {
//     auto countInversions = [](const PuzzleState &state)
//     {
//         vector<int> puzzleArray;
//         for (int i = 0; i < N; i++)
//             for (int j = 0; j < N; j++)
//                 puzzleArray.push_back(state.puzzle[i][j]);

//         int inversions = 0;
//         for (int i = 0; i < puzzleArray.size(); i++)
//         {
//             for (int j = i + 1; j < puzzleArray.size(); j++)
//             {
//                 if (puzzleArray[i] != 0 && puzzleArray[j] != 0 && puzzleArray[i] > puzzleArray[j])
//                     inversions++;
//             }
//         }
//         return inversions;
//     };

//     int initialInversions = countInversions(initial);
//     int goalInversions = countInversions(goal);

//     // Solvable if both have same parity (both even or both odd)
//     return (initialInversions % 2) == (goalInversions % 2);
// }

// PuzzleState getPuzzleState(const string &msg, const PuzzleState &goal, bool isGoal = false)
// {
//     PuzzleState state;
//     cout << msg << " (0 = empty tile):\n";
//     for (int i = 0; i < N; i++)
//         for (int j = 0; j < N; j++)
//         {
//             cout << "Enter value at (" << i << ", " << j << "): ";
//             cin >> state.puzzle[i][j];
//             if (state.puzzle[i][j] == 0)
//             {
//                 state.zeroRow = i;
//                 state.zeroCol = j;
//             }
//         }
//     state.g = 0;
//     state.h = isGoal ? 0 : calcManhattanDistance(state, goal);
//     return state;
// }

// void aStarSearch(const PuzzleState &initial, const PuzzleState &goal)
// {
//     if (!isSolvableForBoth(initial, goal))
//     {
//         cout << "The puzzle is unsolvable (initial and goal states have different parity).\n";
//         return;
//     }

//     priority_queue<PuzzleState> pq;
//     unordered_set<string> visited;

//     pq.push(initial);
//     visited.insert(getHash(initial));

//     while (!pq.empty())
//     {
//         PuzzleState current = pq.top();
//         pq.pop();

//         // Print the current state during search
//         cout << "Current State:\n";
//         printPuzzle(current);

//         if (isEqual(current, goal))
//         {
//             cout << "Goal state reached in " << current.g << " moves.\n";
//             return;
//         }

//         vector<PuzzleState> nextStates = generateNextStates(current, goal);
//         for (const PuzzleState &next : nextStates)
//         {
//             string hash = getHash(next);
//             if (visited.find(hash) == visited.end())
//             {
//                 pq.push(next);
//                 visited.insert(hash);
//             }
//         }
//     }
//     cout << "No solution found.\n";
// }

// int main()
// {
//     PuzzleState goal = getPuzzleState("Enter Goal State", PuzzleState(), true);
//     PuzzleState initial = getPuzzleState("Enter Initial State", goal, false);

//     cout << "Initial State:\n";
//     printPuzzle(initial);
//     cout << "Goal State:\n";
//     printPuzzle(goal);

//     aStarSearch(initial, goal);
//     return 0;
// }

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct Node
{
    int x, y;
    int g, h;
    Node *parent;

    Node(int x, int y, int g, int h, Node *p) : x(x), y(y), g(g), h(h), parent(p) {}

    int f() const { return g + h; }
};

struct CompareNode
{
    bool operator()(const Node *a, const Node *b) const
    {
        return a->f() > b->f();
    }
};

int heuristic(int x, int y, int endX, int endY)
{
    return abs(x - endX) + abs(y - endY);
}

bool isValid(int x, int y, int n, const vector<vector<int>> &grid, const vector<vector<bool>> &visited)
{
    return x >= 0 && x < n && y >= 0 && y < n && grid[x][y] == 0 && !visited[x][y];
}

void printPath(const vector<vector<int>> &grid, Node *endNode, int n)
{
    vector<vector<char>> display(n, vector<char>(n, ' '));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            display[i][j] = grid[i][j] == 1 ? '#' : '0';

    int cost = 0;
    Node *current = endNode;
    while (current != nullptr)
    {
        display[current->x][current->y] = '*';
        cost++;
        current = current->parent;
    }

    cout << "\nCost of path: " << cost - 1 << "\n";
    cout << "Path marked with '*':\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << display[i][j] << " ";
        }
        cout << "\n";
    }
}

void astar(const vector<vector<int>> &grid, int n)
{
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    priority_queue<Node *, vector<Node *>, CompareNode> openSet;
    Node *start = new Node(0, 0, 0, heuristic(0, 0, n - 1, n - 1), nullptr);
    openSet.push(start);

    while (!openSet.empty())
    {
        Node *current = openSet.top();
        openSet.pop();

        int x = current->x;
        int y = current->y;

        if (visited[x][y])
            continue;
        visited[x][y] = true;

        if (x == n - 1 && y == n - 1)
        {
            printPath(grid, current, n);
            return;
        }

        for (auto dir : directions)
        {
            int nx = x + dir.first;
            int ny = y + dir.second;

            if (isValid(nx, ny, n, grid, visited))
            {
                int g = current->g + 1;
                int h = heuristic(nx, ny, n - 1, n - 1);
                Node *neighbor = new Node(nx, ny, g, h, current);
                openSet.push(neighbor);
            }
        }
    }

    cout << "No path found!\n";
}

int main()
{
    int n;
    cout << "Enter grid size (n): ";
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n));
    cout << "Enter grid values (0 = open, 1 = blocked):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
    {
        cout << "Start or End is blocked!\n";
        return 0;
    }

    astar(grid, n);
    return 0;
}
