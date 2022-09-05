#include <bits/stdc++.h>
using namespace std;

void depthFirstSearch(int node, int parent_node, vector<int> &depth,
                      const vector<vector<int>> &graph)
{
    depth[node] = (parent_node < 0 ? 0 : depth[parent_node] + 1);
    for (int neighbour : graph[node])
    {
        if (neighbour != parent_node)
        {
            depthFirstSearch(neighbour, node, depth, graph);
        }
    }
}

pair<int, int> findFarthestNode(int root, int graph_size, const vector<vector<int>> &graph)
{
    int best_node = -1;
    vector<int> depth(graph_size, 0);
    depthFirstSearch(root, -1, depth, graph);
    for (int node = 0; node < graph_size; ++node)
    {
        if (best_node == -1 || (depth[best_node] < depth[node] && depth[node] != -1))
        {
            best_node = node;
        }
    }
    return make_pair(best_node, depth[best_node]);
}

int getDiameter(int root, int graph_size, const vector<vector<int>> &graph)
{
    int first_node = findFarthestNode(root, graph_size, graph).first;
    return findFarthestNode(first_node, graph_size, graph).second;
}

int main()
{
    int graph_size;
    cin >> graph_size;
    vector<vector<int>> graph(graph_size);
    for (int i = 1; i < graph_size; ++i)
    {
        int first_node, second_node;
        cin >> first_node >> second_node;
        --first_node, --second_node;
        graph[first_node].emplace_back(second_node);
        graph[second_node].emplace_back(first_node);
    }
    cout << getDiameter(0, graph_size, graph) << "\n";
    return 0;
}