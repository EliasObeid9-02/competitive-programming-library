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

int main()
{
    int array_size, queries;
    cin >> array_size >> queries;

    vector<int> initial_array(array_size);
    for (int i = 0; i < array_size; ++i)
    {
        cin >> initial_array[i];
    }

    SegmentTree<false> segment_tree(array_size, initial_array);
    for (int i = 0; i < queries; ++i)
    {
        string operation;
        cin >> operation;
        if (operation == "set")
        {
            int index, value;
            cin >> index >> value;
            segment_tree.updateTree(index, value);
        }
        else if (operation == "query")
        {
            int left_bound, right_bound;
            cin >> left_bound >> right_bound;
            cout << segment_tree.queryRange(left_bound, right_bound).maximum << "\n";
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}