#include <bits/stdc++.h>
using namespace std;

template <bool one_indexing_mode = false>
class SegmentTree
{
public:
    // Todo : modify based on problem requirements
    struct Segment
    {
        int maximum;
        Segment(int _maximum = numeric_limits<int>::lowest()) : maximum{_maximum} {}

        friend Segment operator+(const Segment &left_side, const Segment &right_side)
        {
            return Segment(max(left_side.maximum, right_side.maximum));
        }
    };

private:
    int tree_size;
    int tree_range_start, tree_range_end;
    vector<Segment> segment_tree;

    void initialize(int array_size)
    {
        tree_size = 1;
        while (tree_size < array_size)
        {
            tree_size *= 2;
        }

        if (one_indexing_mode)
        {
            tree_range_start = 1;
            tree_range_end = tree_size;
        }
        else
        {
            tree_range_start = 0;
            tree_range_end = tree_size - 1;
        }

        segment_tree.resize(tree_size * 2, Segment{});
    }

    template <typename value_type = int>
    void buildTree(int array_size, const vector<value_type> &initial_array = vector<value_type>{})
    {
        if (initial_array.empty())
        {
            return;
        }

        for (int i = 0; i < array_size; ++i)
        {
            int index = i + (int)one_indexing_mode;
            segment_tree[tree_size + i] = Segment(initial_array[index]);
        }

        for (int node = tree_size - 1; node > 0; --node)
        {
            segment_tree[node] = segment_tree[node * 2] + segment_tree[node * 2 + 1];
        }
    }

    void updateTree(int index, int value, int node, int low, int high)
    {
        if (low == high)
        {
            segment_tree[node] = Segment(value);
        }
        else
        {
            int middle = low + (high - low) / 2;
            if (index <= middle)
            {
                updateTree(index, value, node * 2, low, middle);
            }
            else
            {
                updateTree(index, value, node * 2 + 1, middle + 1, high);
            }
            segment_tree[node] = segment_tree[node * 2] + segment_tree[node * 2 + 1];
        }
    }

    Segment queryRange(int left_bound, int right_bound, int node, int low, int high)
    {
        if (right_bound < low || high < left_bound)
        {
            return Segment();
        }
        else if (left_bound <= low && high <= right_bound)
        {
            return segment_tree[node];
        }
        else
        {
            int middle = low + (high - low) / 2;
            return (queryRange(left_bound, right_bound, node * 2, low, middle) +
                    queryRange(left_bound, right_bound, node * 2 + 1, middle + 1, high));
        }
    }

public:
    SegmentTree() {}

    template <typename value_type = int>
    SegmentTree(int array_size, const vector<value_type> &initial_array = vector<value_type>{})
    {
        this->initialize(array_size);
        this->buildTree(array_size, initial_array);
    }

    void updateTree(int index, int value)
    {
        updateTree(index, value, 1, tree_range_start, tree_range_end);
    }

    Segment queryRange(int left_bound, int right_bound)
    {
        return queryRange(left_bound, right_bound, 1, tree_range_start, tree_range_end);
    }
};

template <bool one_indexing_mode = false, bool values_in_edges = false>
class HeavyLightDecomposition
{
private:
    struct Edge
    {
        int neighbour, weight;
        Edge(int _neighbour = -1, int _weight = 0) : neighbour{_neighbour}, weight{_weight} {}

        friend bool operator==(const Edge &first_edge, const Edge &second_edge)
        {
            return (first_edge.neighbour == second_edge.neighbour &&
                    first_edge.weight == second_edge.weight);
        }
    };

    static int getHighestBit(int value)
    {
        return (value == 0 ? -1 : 31 - __builtin_clz(value));
    }

    int graph_size, lca_levels;
    vector<vector<Edge>> graph;
    vector<vector<int>> parent;
    vector<int> depth, time_in, time_out, decoded, chain_root, subtree_size;
    vector<long long> distances;
    SegmentTree<false> segment_tree;

    void initialize(int _graph_size)
    {
        graph_size = _graph_size + (int)one_indexing_mode;
        lca_levels = getHighestBit(graph_size) + 1;
        graph.resize(graph_size);
        parent.resize(graph_size, vector<int>(lca_levels + 1, -1));
        depth.resize(graph_size);
        time_in.resize(graph_size);
        time_out.resize(graph_size);
        decoded.resize(graph_size);
        chain_root.resize(graph_size);
        subtree_size.resize(graph_size);
        distances.resize(graph_size);
        segment_tree = SegmentTree<false>(graph_size);
    }

    bool isAncestor(int first_node, int second_node)
    {
        return (time_in[first_node] <= time_in[second_node] &&
                time_out[first_node] >= time_out[second_node]);
    }

    int getSubtreeSize(int node, int node_parent, int edge_weight)
    {
        parent[node][0] = node_parent;
        for (int level = 1; level <= lca_levels; ++level)
        {
            parent[node][level] = parent[parent[node][level - 1]][level - 1];
        }
        subtree_size[node] = 1;
        depth[node] = (node_parent == node ? 0 : depth[node_parent] + 1);
        distances[node] = (node_parent == node ? 0 : distances[node_parent] + edge_weight);
        for (auto &neighbour_node : graph[node])
        {
            auto &[neighbour, weight] = neighbour_node;
            graph[neighbour].erase(find(graph[neighbour].begin(), graph[neighbour].end(), Edge(node, weight)));
            subtree_size[node] += getSubtreeSize(neighbour, node, weight);
            if (subtree_size[neighbour] > subtree_size[graph[node][0].neighbour])
            {
                swap(neighbour_node, graph[node][0]);
            }
        }
        return subtree_size[node];
    }

    void builderDepthFirstSearch(int node, int current_root, int edge_weight, int &timer)
    {
        time_in[node] = ++timer;
        decoded[time_in[node]] = node;
        chain_root[node] = current_root;

        if (values_in_edges)
        {
            segment_tree.updateTree(time_in[node], edge_weight);
        }

        for (const auto &[neighbour, weight] : graph[node])
        {
            int new_root = (neighbour == graph[node][0].neighbour ? current_root : neighbour);
            builderDepthFirstSearch(neighbour, new_root, weight, timer);
        }
        time_out[node] = timer;
    }

public:
    HeavyLightDecomposition() {}

    HeavyLightDecomposition(int _graph_size)
    {
        initialize(_graph_size);
    }

    void addEdge(int first_node, int second_node, int weight = 1)
    {
        graph[first_node].emplace_back(second_node, weight);
        graph[second_node].emplace_back(first_node, weight);
    }

    template <typename value_type = int>
    void buildHLD(int root = (int)one_indexing_mode, const vector<value_type> &values = vector<value_type>{})
    {
        int timer = -1;
        getSubtreeSize(root, root, 0);
        builderDepthFirstSearch(root, root, 0, timer);

        if (!values.empty())
        {
            vector<value_type> actual_values(graph_size);
            for (int node = (int)one_indexing_mode; node < graph_size; ++node)
            {
                actual_values[time_in[node]] = values[node];
            }
            segment_tree = SegmentTree<false>(graph_size, actual_values);
        }
    }

    SegmentTree<false>::Segment queryPath(int first_node, int second_node)
    {
        SegmentTree<false>::Segment result{};
        for (; chain_root[first_node] != chain_root[second_node]; second_node = parent[chain_root[second_node]][0])
        {
            if (depth[chain_root[first_node]] > depth[chain_root[second_node]])
            {
                swap(first_node, second_node);
            }
            int left_bound = time_in[chain_root[second_node]], right_bound = time_in[second_node];
            result = result + segment_tree.queryRange(left_bound, right_bound);
        }

        if (depth[first_node] > depth[second_node])
        {
            swap(first_node, second_node);
        }
        int left_bound = time_in[first_node] + (int)values_in_edges, right_bound = time_in[second_node];
        result = result + segment_tree.queryRange(left_bound, right_bound);
        return result;
    }

    void updateNode(int node, int value)
    {
        segment_tree.updateTree(time_in[node], value);
    }

    void updateEdge(int first_node, int second_node, int value)
    {
        if (depth[first_node] < depth[second_node])
        {
            swap(first_node, second_node);
        }
        updateNode(first_node, value);
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
    int graph_size, queries_count;
    cin >> graph_size >> queries_count;

    vector<int> values(graph_size + 1);
    for (int node = 1; node <= graph_size; ++node)
    {
        cin >> values[node];
    }

    HeavyLightDecomposition<true> hld(graph_size);
    for (int edge = 1; edge < graph_size; ++edge)
    {
        int first_node, second_node;
        cin >> first_node >> second_node;
        hld.addEdge(first_node, second_node);
    }
    hld.buildHLD(1, values);

    for (int query = 0; query < queries_count; ++query)
    {
        string query_type;
        cin >> query_type;
        if (query_type == "set")
        {
            int node, value;
            cin >> node >> value;
            hld.updateNode(node, value);
        }
        else if (query_type == "sum")
        {
            int first_node = 1, second_node;
            cin >> second_node;
            cout << hld.queryPath(first_node, second_node).maximum << "\n";
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}