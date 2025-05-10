#include <bits/stdc++.h>
using namespace std;

struct Job
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;

    Job(int id, int arrivalTime, int burstTime) : id(id), arrivalTime(arrivalTime), burstTime(burstTime), remainingTime(burstTime) {}
};

class Solution
{
public:
    void FCFS();
    void dijkstra(const unordered_map<int, vector<pair<int, int>>> &graph, int source);
};

void Solution::FCFS() // Now FCFS
{
    vector<Job> jobs;
    int n;
    cout << "Enter the total number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int at, bt;
        cout << "Enter the Arrival Time of Process " << i + 1 << ": ";
        cin >> at;
        cout << "Enter the Burst Time of Process " << i + 1 << ": ";
        cin >> bt;

        if (at < 0 || bt <= 0)
        {
            cout << "Invalid input! Arrival time must be >= 0 and Burst time > 0.\n";
            return;
        }
        jobs.push_back(Job(i + 1, at, bt));
    }

    // Sort by arrival time
    sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
         { return a.arrivalTime < b.arrivalTime; });

    int currentTime = 0;
    vector<int> completionTime(n), turnaroundTime(n), waitingTime(n);

    cout << "\nGantt Chart:\n";
    cout << "-----------------------------------------\n|";

    for (int i = 0; i < n; ++i)
    {
        if (currentTime < jobs[i].arrivalTime)
        {
            currentTime = jobs[i].arrivalTime; // CPU idle till job arrives
        }

        currentTime += jobs[i].burstTime;
        completionTime[i] = currentTime;
        turnaroundTime[i] = completionTime[i] - jobs[i].arrivalTime;
        waitingTime[i] = turnaroundTime[i] - jobs[i].burstTime;

        cout << " P" << jobs[i].id << " |";
    }

    cout << "\n-----------------------------------------\n";

    currentTime = 0;
    cout << "0";
    for (int i = 0; i < n; ++i)
    {
        if (currentTime < jobs[i].arrivalTime)
        {
            currentTime = jobs[i].arrivalTime;
        }
        currentTime += jobs[i].burstTime;
        cout << setw(5) << currentTime;
    }

    // Display stats
    double totalWT = 0, totalTAT = 0;
    cout << "\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "P" << jobs[i].id << "\t" << jobs[i].arrivalTime << "\t"
             << jobs[i].burstTime << "\t" << completionTime[i] << "\t"
             << turnaroundTime[i] << "\t" << waitingTime[i] << "\n";

        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }

    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << "\n";
}

void Solution::dijkstra(const unordered_map<int, vector<pair<int, int>>> &graph, int source)
{
    unordered_map<int, int> dist;
    for (const auto &entry : graph)
    {
        dist[entry.first] = INT_MAX;
    }
    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u])
            continue;

        for (const auto &neighbor : graph.at(u))
        {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest distances from source " << source << ":\n";
    for (const auto &entry : dist)
    {
        if (entry.second == INT_MAX)
        {
            cout << "Node " << entry.first << ": INF\n";
        }
        else
        {
            cout << "Node " << entry.first << ": " << entry.second << "\n";
        }
    }
}

int main()
{
    int choice;
    Solution sl;

    do
    {
        cout << endl;
        cout << "1. Job Scheduling (Round Robin Algorithm)" << endl;
        cout << "2. Single-Source Shortest Path Problem (Dijkstra)" << endl;
        cout << "0. Exit" << endl;
        cout << endl;
        cout << "Enter your CHOICE: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            sl.FCFS();
            break;
        case 2:
        {
            int source;
            unordered_map<int, vector<pair<int, int>>> graph;
            int edges, u, v, w;
            cout << "Enter number of edges: ";
            cin >> edges;
            for (int i = 0; i < edges; ++i)
            {
                cout << "Enter edge (u v w): ";
                cin >> u >> v >> w;
                graph[u].push_back({v, w});
                graph[v].push_back({u, w});
            }
            cout << "Enter source node: ";
            cin >> source;
            sl.dijkstra(graph, source);
            break;
        }
        case 0:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice! Please select a valid option." << endl;
            break;
        }

    } while (choice != 0); // Corrected condition to exit the loop when choice is 0.

    return 0;
}
