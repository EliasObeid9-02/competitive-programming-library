#include <bits/stdc++.h>
using namespace std;

template <bool one_indexing_mode = false>
class LCA
{
private:
    struct Edge
    {
        int neighbour, weight;
        Edge(int _neighbour = -1, int _weight = 0) : neighbour{_neighbour}, weight{_weight} {}
    };

    static int getHighestBit(int value)
    {
        return (value == 0 ? -1 : 31 - __builtin_clz(value));
    }

    int graph_size, lca_levels;
    vector<vector<Edge>> graph;
    vector<vector<int>> parent;
    vector<long long> distances;
    vector<int> depth, time_in, time_out;

    bool isAncestor(int first_node, int second_node)
    {
        return (time_in[first_node] <= time_in[second_node] &&
                time_out[first_node] >= time_out[second_node]);
    }

    void depthFirstSearch(int node, int parent_node, int edge_weight, int &timer)
    {
        distances[node] = (parent_node == node ? 0 : distances[parent_node] + edge_weight);
        depth[node] = (parent_node == node ? 0 : depth[parent_node] + 1);
        parent[node][0] = parent_node;
        for (int level = 1; level <= lca_levels; ++level)
        {
            parent[node][level] = parent[parent[node][level - 1]][level - 1];
        }

        time_in[node] = ++timer;
        for (const auto &[neighbour, weight] : graph[node])
        {
            if (neighbour != parent_node)
            {
                depthFirstSearch(neighbour, node, weight, timer);
            }
        }
        time_out[node] = ++timer;
    }

public:
    LCA() {}
    LCA(int _graph_size) : graph_size{_graph_size + (int)one_indexing_mode},
                           lca_levels{getHighestBit(graph_size) + 1},
                           graph(graph_size), parent(graph_size, vector<int>(lca_levels + 1, -1)),
                           distances(graph_size, 0), depth(graph_size, 0),
                           time_in(graph_size, 0), time_out(graph_size, 0) {}

    void addEdge(int first_node, int second_node, int weight = 1)
    {
        graph[first_node].emplace_back(second_node, weight);
        graph[second_node].emplace_back(first_node, weight);
    }

    void buildLCA(int root = (int)one_indexing_mode)
    {
        int timer = 0;
        depthFirstSearch(root, root, 0, timer);
    }

    int getLCA(int first_node, int second_node)
    {
        if (isAncestor(first_node, second_node))
        {
            return first_node;
        }
        else if (isAncestor(second_node, first_node))
        {
            return second_node;
        }
        else
        {
            for (int level = lca_levels; level >= 0; --level)
            {
                if (!isAncestor(parent[first_node][level], second_node))
                {
                    first_node = parent[first_node][level];
                }
            }
            return parent[first_node][0];
        }
    }

    int kthAncestor(int node, int ancestor_order)
    {
        if (ancestor_order > depth[node])
        {
            return -2 + (int)one_indexing_mode;
        }

        for (int level = lca_levels; level >= 0; --level)
        {
            if (ancestor_order > 0 && (1 << level) <= ancestor_order)
            {
                node = parent[node][level];
                ancestor_order -= (1 << level);
            }
        }
        return (ancestor_order == 0 ? node : (int)one_indexing_mode);
    }

    int getKthNodeOnPath(int first_node, int second_node, int order)
    {
        int common_ancestor = getLCA(first_node, second_node);
        int first_half = depth[first_node] - depth[common_ancestor];
        int second_half = depth[second_node] - depth[common_ancestor];
        if (order < first_half)
        {
            return kthAncestor(first_node, order);
        }
        else
        {
            return kthAncestor(second_node, first_half + second_half - order);
        }
    }

    int getDistance(int first_node, int second_node)
    {
        return distances[first_node] + distances[second_node] -
               2 * distances[getLCA(first_node, second_node)];
    }

    bool onPath(int first_node, int second_node, int middle_node)
    {
        return ((isAncestor(first_node, middle_node) && isAncestor(middle_node, second_node)) ||
                (isAncestor(second_node, middle_node) && isAncestor(middle_node, first_node)));
    }
};

int main()
{
    int graph_size, queries;
    cin >> graph_size >> queries;

    LCA<true> graph(graph_size);
    for (int node = 1; node < graph_size; ++node)
    {
        int parent_node;
        cin >> parent_node;
        graph.addEdge(parent_node, node);
    }
    graph.buildLCA();

    for (int i = 0; i < queries; ++i)
    {
        string type;
        cin >> type;

        if (type == "common")
        {
            int first_node, second_node;
            cin >> first_node >> second_node;
            cout << graph.getLCA(first_node, second_node) + 1 << "\n";
        }
        else if (type == "kth")
        {
            int node, ancestor_order;
            cin >> node >> ancestor_order;
            cout << graph.kthAncestor(node, ancestor_order) << "\n";
        }
    }
    return 0;
}