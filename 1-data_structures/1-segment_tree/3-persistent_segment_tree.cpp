#include <bits/stdc++.h>
using namespace std;

class PersistentSegmentTree
{
private:
    struct Segment
    {
        long long sum;
        Segment(long long _sum = 0) : sum{_sum} {}

        friend Segment operator+(const Segment &left_side, const Segment &right_side)
        {
            return Segment(left_side.sum + right_side.sum);
        }
    };

    struct Node
    {
        int left_child, right_child;
        Segment values;
        Node(int _left_child = -1, int _right_child = -1, const Segment &_values = Segment{})
            : left_child{_left_child}, right_child{_right_child}, values{_values} {}
    };

    int left(int node) { return segment_tree[node].left_child; }
    int right(int node) { return segment_tree[node].right_child; }
    Segment &values(int node) { return segment_tree[node].values; }
    const Segment &values(int node) const { return segment_tree[node].values; }
    void setLeft(int node, int new_child) { segment_tree[node].left_child = new_child; }
    void setRight(int node, int new_child) { segment_tree[node].right_child = new_child; }

    int fetchNode(int node)
    {
        segment_tree.emplace_back(segment_tree[node]);
        return (int)segment_tree.size() - 1;
    }

    int tree_size, tree_height;
    vector<Node> segment_tree;

    void initialize(int array_size, int query_count = 0)
    {
        tree_size = 1;
        tree_height = 0;
        while (tree_size < array_size)
        {
            tree_size *= 2;
            ++tree_height;
        }
        segment_tree.reserve(2 * tree_size + query_count * tree_height);
        segment_tree.resize(2 * tree_size);

        for (int node = 1; node < tree_size; ++node)
        {
            segment_tree[node].left_child = node * 2;
            segment_tree[node].right_child = node * 2 + 1;
        }
    }

    void buildTree(int array_size, const vector<int> &initial_array)
    {
        for (int i = 0; i < array_size; ++i)
        {
            values(i + tree_size) = Segment(initial_array[i]);
        }

        for (int node = tree_size - 1; node > 1; --node)
        {
            values(node) = values(left(node)) + values(right(node));
        }
    }

    Segment queryRange(int left_bound, int right_bound, int node, int low, int high)
    {
        if (left_bound <= low && high <= right_bound)
        {
            return values(node);
        }
        else if (right_bound < low || high < left_bound)
        {
            return Segment();
        }
        else
        {
            int middle = low + (high - low) / 2;
            return (queryRange(left_bound, right_bound, left(node), low, middle) +
                    queryRange(left_bound, right_bound, right(node), middle + 1, high));
        }
    }

    int updateTree(int index, int new_value, int node, int low, int high)
    {
        node = fetchNode(node);
        if (low == high)
        {
            values(node) = Segment(new_value);
        }
        else
        {
            int middle = low + (high - low) / 2;
            if (index <= middle)
            {
                setLeft(node, updateTree(index, new_value, left(node), low, middle));
            }
            else
            {
                setRight(node, updateTree(index, new_value, right(node), middle + 1, high));
            }
            values(node) = values(left(node)) + values(right(node));
        }
        return node;
    }

public:
    PersistentSegmentTree() {}
    PersistentSegmentTree(int array_size, int query_count = 0)
    {
        this->initialize(array_size, query_count);
    }

    PersistentSegmentTree(int array_size, const vector<int> &initial_array, int query_count = 0)
    {
        this->initialize(array_size, query_count);
        this->buildTree(array_size, initial_array);
    }

    Segment queryRange(int left_bound, int right_bound, int root)
    {
        return queryRange(left_bound, right_bound, root, 0, tree_size - 1);
    }

    int updateTree(int index, int new_value, int root)
    {
        return updateTree(index, new_value, root, 0, tree_size - 1);
    }
};

const int maximum_value = 1'000'000;

int main()
{
    int array_size;
    cin >> array_size;

    vector<int> roots(array_size + 1, 1);
    vector<int> last_position(maximum_value + 1, 0);
    PersistentSegmentTree segment_tree(array_size + 1, array_size + 1);

    for (int i = 1; i <= array_size; ++i)
    {
        int value;
        cin >> value;
        roots[i] = segment_tree.updateTree(i, 1, roots[i - 1]);
        if (last_position[value] > 0)
        {
            roots[i] = segment_tree.updateTree(last_position[value], 0, roots[i]);
        }
        last_position[value] = i;
    }

    int queries;
    cin >> queries;

    for (int i = 0; i < queries; ++i)
    {
        int left_bound, right_bound;
        cin >> left_bound >> right_bound;
        cout << segment_tree.queryRange(left_bound, right_bound, roots[right_bound]).sum << "\n";
    }
    return 0;
}