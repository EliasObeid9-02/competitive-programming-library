#include <bits/stdc++.h>
using namespace std;

const long long INF = 1'000'000'000LL * 1'000'000'000;

struct Path
{
    int node;
    long long weight;
    Path(int _node = 0, long long _weight = 0) : node{_node}, weight{_weight} {}

    friend bool operator<(const Path &A, const Path &B)
    {
        return A.weight < B.weight;
    }
};

vector<long long> getDijkstra(int source, int graph_size, const vector<vector<pair<int, int>>> &graph)
{
    vector<long long> distances(graph_size + 1, INF);
    distances[source] = 0;

    priority_queue<Path, vector<Path>> paths;
    for (int node = 1; node <= graph_size; ++node)
    {
        paths.emplace(node, distances[node]);
    }

    while (!paths.empty())
    {
        auto [node, path_weight] = paths.top();
        paths.pop();

        if (path_weight > distances[node])
        {
            continue;
        }

        for (const auto &[neighbour, weight] : graph[node])
        {
            if (distances[neighbour] > weight + path_weight)
            {
                distances[neighbour] = weight + path_weight;
                paths.emplace(neighbour, distances[neighbour]);
            }
        }
    }
    return distances;
}

long long getNodeDistance(int node, const vector<long long> &distances)
{
    return (distances[node] == INF ? -1 : distances[node]);
}

int main()
{
    int graph_size, edges_count, queries, source;
    cin >> graph_size >> edges_count >> queries >> source;
    --source;

    vector<vector<pair<int, int>>> graph(graph_size);
    for (int i = 0; i < edges_count; ++i)
    {
        int first_node, second_node, weight;
        cin >> first_node >> second_node >> weight;
        --first_node, --second_node;
        graph[first_node].emplace_back(second_node, weight);
        graph[second_node].emplace_back(first_node, weight);
    }

    vector<long long> distances = getDijkstra(source, graph_size, graph);
    for (int i = 0; i < queries; ++i)
    {
        int node;
        cin >> node;
        cout << getNodeDistance(node, distances) << "\n";
    }
    return 0;
}