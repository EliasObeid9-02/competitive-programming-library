#include <bits/stdc++.h>
using namespace std;

// ! assumes the graph is a DAG
vector<int> topologicalSort(int graph_size, const vector<vector<int>> &graph)
{
    vector<int> in_degree(graph_size);
    for (int node = 0; node < graph_size; ++node)
    {
        for (int neighbour : graph[node])
        {
            ++in_degree[neighbour];
        }
    }

    vector<int> order;
    vector<bool> visited(graph_size, false);
    for (int node = 0; node < graph_size; ++node)
    {
        if (in_degree[node] == 0)
        {
            visited[node] = true;
            order.emplace_back(node);
        }
    }

    for (int i = 0; i < (int)order.size(); ++i)
    {
        int node = order[i];
        for (int neighbour : graph[node])
        {
            --in_degree[neighbour];
            if (in_degree[neighbour] == 0)
            {
                visited[neighbour] = true;
                order.emplace_back(neighbour);
            }
        }
    }
    reverse(order.begin(), order.end());
    return order;
}

int main()
{
    int graph_size, edges_count;
    cin >> graph_size >> edges_count;

    vector<vector<int>> graph(graph_size);
    for (int i = 0; i < edges_count; ++i)
    {
        int first_node, second_node;
        cin >> first_node >> second_node;
        --first_node, --second_node;
        graph[first_node].emplace_back(second_node);
    }

    vector<int> topological_order = topologicalSort(graph_size, graph);
    for (int node : topological_order)
    {
        cout << node + 1 << " \n"[node == topological_order.back()];
    }
    return 0;
}