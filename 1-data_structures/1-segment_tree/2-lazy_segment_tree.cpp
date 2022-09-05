#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
private:
    // Todo : modify based on problem requirements
    struct Change
    {
        const static int IDENTITY = numeric_limits<int>::lowest();

        long long to_add;
        int to_set;
        Change(long long _to_add = 0, int _to_set = IDENTITY)
            : to_add{_to_add}, to_set{_to_set}
        {
        }

        bool hasSet() const
        {
            return to_set != IDENTITY;
        }

        bool hasChange() const
        {
            return hasSet() || to_add != 0;
        }

        void combineChanges(const Change &other)
        {
            if (other.hasSet())
            {
                *this = other;
            }
            else
            {
                to_add += other.to_add;
            }
        }
    };

    // Todo : modify based on problem requirements
    struct Segment
    {
        long long sum, minimum, maximum;
        Segment(long long _sum = 0,
                long long _minimum = numeric_limits<long long>::max(),
                long long _maximum = numeric_limits<long long>::lowest())
            : sum{_sum}, minimum{_minimum}, maximum{_maximum} {}

        void pushChange(const Change &change, int low, int high)
        {
            if (change.hasSet())
            {
                sum = change.to_set * (high - low + 1LL);
                minimum = maximum = change.to_set;
            }
            sum += change.to_add * (high - low + 1LL);
            minimum += change.to_add;
            maximum += change.to_add;
        }

        friend Segment operator+(const Segment &left_side, const Segment &right_side)
        {
            return Segment(left_side.sum + right_side.sum,
                           min(left_side.minimum, right_side.minimum),
                           max(left_side.maximum, right_side.maximum));
        }
    };

    int tree_size;
    vector<Segment> segment_tree;
    vector<Change> lazy_tree;

    void initialize(int array_size)
    {
        tree_size = 1;
        while (tree_size < array_size)
        {
            tree_size *= 2;
        }
        segment_tree.resize(tree_size * 2, Segment{});
        lazy_tree.resize(tree_size * 2, Change{});
    }

    void buildTree(int array_size, const vector<int> &initial_array)
    {
        for (int i = 0; i < array_size; ++i)
        {
            segment_tree[tree_size + i] = Segment(initial_array[i], initial_array[i], initial_array[i]);
        }

        for (int node = tree_size - 1; node > 0; --node)
        {
            segment_tree[node] = segment_tree[node * 2] + segment_tree[node * 2 + 1];
        }
    }

    // Todo : modify based on problem requirements
    void pushUpdates(int node, int low, int high)
    {
        if (lazy_tree[node].hasChange())
        {
            segment_tree[node].pushChange(lazy_tree[node], low, high);
            if (low != high)
            {
                lazy_tree[node * 2].combineChanges(lazy_tree[node]);
                lazy_tree[node * 2 + 1].combineChanges(lazy_tree[node]);
            }
            lazy_tree[node] = Change{};
        }
    }

    void updateRange(int left_bound, int right_bound, int adding_value, int setting_value,
                     int node, int low, int high)
    {
        pushUpdates(node, low, high);
        if (right_bound < low || high < left_bound)
        {
            return;
        }
        else if (left_bound <= low && high <= right_bound)
        {
            lazy_tree[node].combineChanges(Change(adding_value, setting_value));
            pushUpdates(node, low, high);
        }
        else
        {
            int middle = low + (high - low) / 2;
            updateRange(left_bound, right_bound, adding_value, setting_value, node * 2, low, middle);
            updateRange(left_bound, right_bound, adding_value, setting_value, node * 2 + 1, middle + 1, high);
            segment_tree[node] = segment_tree[node * 2] + segment_tree[node * 2 + 1];
        }
    }

    Segment queryRange(int left_bound, int right_bound, int node, int low, int high)
    {
        pushUpdates(node, low, high);
        if (right_bound < low || high < left_bound)
        {
            return Segment{};
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
    SegmentTree(int array_size)
    {
        initialize(array_size);
    }

    SegmentTree(int array_size, const vector<int> &initial_array)
    {
        initialize(array_size);
        buildTree(array_size, initial_array);
    }

    void updateRange(int left_bound, int right_bound, int adding_value)
    {
        updateRange(left_bound, right_bound, adding_value, Change::IDENTITY, 1, 0, tree_size - 1);
    }

    void updateRange(int left_bound, int right_bound, int adding_value, int setting_value)
    {
        updateRange(left_bound, right_bound, adding_value, setting_value, 1, 0, tree_size - 1);
    }

    Segment queryRange(int left_bound, int right_bound)
    {
        return queryRange(left_bound, right_bound, 1, 0, tree_size - 1);
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

    SegmentTree segment_tree(array_size, initial_array);
    for (int i = 0; i < queries; ++i)
    {
        string operation;
        cin >> operation;
        if (operation == "set")
        {
            int left_bound, right_bound, setting_value;
            cin >> left_bound >> right_bound >> setting_value;
            segment_tree.updateRange(left_bound, right_bound, 0, setting_value);
        }
        else if (operation == "add")
        {
            int left_bound, right_bound, adding_value;
            cin >> left_bound >> right_bound >> adding_value;
            segment_tree.updateRange(left_bound, right_bound, adding_value);
        }
        else if (operation == "query")
        {
            int left_bound, right_bound;
            cin >> left_bound >> right_bound;
            cout << segment_tree.queryRange(left_bound, right_bound).sum << "\n";
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}