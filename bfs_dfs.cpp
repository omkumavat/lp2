#include <bits/stdc++.h>
using namespace std;

void BFSHelper(queue<int> q, vector<bool> &vis, unordered_map<int, vector<int>> &adj)
{
    if (q.empty())
        return;

    int level = q.size();
    queue<int> nextL;

    while (level--)
    {
        int node = q.front();
        q.pop();
        cout << node << " ";
        for (int it : adj[node])
        {
            if (!vis[it])
            {
                vis[it] = true;
                nextL.push(it);
            }
        }
    }
    cout << endl;

    BFSHelper(nextL, vis, adj);
}

void DFSHelper(int node, vector<bool> &vis, unordered_map<int, vector<int>> &adj)
{
    if (vis[node])
        return;

    cout << node << " ";
    vis[node] = true;

    for (int it : adj[node])
    {
        if (!vis[it])
        {
            DFSHelper(it, vis, adj);
        }
    }
}

class BFSDFS
{
    unordered_map<int, vector<int>> adj;
    int n, m;

public:
    BFSDFS(unordered_map<int, vector<int>> adjc, int nc, int mc)
    {
        n = nc;
        m = mc;
        adj = adjc;
    }
    void BFS();
    void DFS();
};

void BFSDFS::BFS()
{

    int start;
    cout << "Enter starting node for BFS Traversal : ";
    cin >> start;

    queue<int> q;
    q.push(start);
    vector<bool> vis(n + 1, false);
    vis[start] = true;
    cout << "BFS Traversal : " << endl;
    BFSHelper(q, vis, adj);
}
void BFSDFS::DFS()
{
    int start;
    cout << "Enter starting node for DFS Traversal : ";
    cin >> start;

    vector<bool> vis(n + 1, false);
    cout << "DFS Traversal : " << endl;
    DFSHelper(start, vis, adj);
}
int main()
{
    unordered_map<int, vector<int>> adj;
    int n, m;
    cout << "Enter the number of nodes: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;

    cout << "Enter the edges: " << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cout << "Enter the starting node of " << i + 1 << "th edge : ";
        cin >> u;
        cout << "Enter the ending node of " << i + 1 << "th edge : ";
        cin >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    BFSDFS bfsdfs = BFSDFS(adj, n, m);

    int choice;
    cout << "Enter 1 for BFS Traversal and 2 for DFS Traversal: ";
    cin >> choice;

    while (choice != 0)
    {
        if (choice == 1)
        {
            bfsdfs.BFS();
        }
        else if (choice == 2)
        {
            bfsdfs.DFS();
        }
        else
        {
            cout << "Invalid choice. Please enter 1 or 2." << endl;
        }

        cout << "Enter 1 for BFS Traversal and 2 for DFS Traversal: ";
        cin >> choice;
    }

    return 0;
    ;
}
