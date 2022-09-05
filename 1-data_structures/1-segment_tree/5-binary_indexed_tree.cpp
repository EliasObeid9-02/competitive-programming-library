#include <bits/stdc++.h>
using namespace std;

template <typename number_type, bool one_indexing_mode = false>
class BIT
{
private:
    int tree_size;
    vector<number_type> tree;

    static int getHighestBit(int value)
    {
        return (value == 0 ? -1 : 31 - __builtin_clz(value));
    }

public:
    BIT() {}
    BIT(int array_size) : tree_size{array_size + (int)one_indexing_mode}, tree(tree_size) {}

    void updateTree(int index, number_type addition)
    {
        for (int i = index; i < tree_size;
             i = (one_indexing_mode ? i + (i & (-i)) : i | (i + 1)))
        {
            tree[i] += addition;
        }
    }

    void updateRange(int left_bound, int right_bound, number_type addition)
    {
        updateTree(left_bound, +addition);
        updateTree(right_bound + 1, -addition);
    }

    number_type queryPrefix(int right_bound)
    {
        number_type sum{};
        for (int i = right_bound; i >= 0 + (int)one_indexing_mode;
             i = (one_indexing_mode ? i - (i & (-i)) : (i & (i + 1)) - 1))
        {
            sum += tree[i];
        }
        return sum;
    }

    number_type queryRange(int left_bound, int right_bound)
    {
        if (left_bound > right_bound)
        {
            return number_type{};
        }
        return queryPrefix(right_bound) - queryPrefix(left_bound - 1);
    }

    // ! Only works in 1-indexing mode
    // returns the first index such that prefix_sums[index] >= target_sum
    int findFirstPrefix(number_type target_sum)
    {
        int index = 0;
        number_type current_sum{};
        for (int bit = getHighestBit(tree_size); bit >= 0; --bit)
        {
            int offset = (1 << bit);
            if (index + offset < tree_size && current_sum + tree[index + offset] < target_sum)
            {
                current_sum += tree[index + offset];
                index += offset;
            }
        }
        return index + 1;
    }
};

int main()
{
    int array_size, queries;
    cin >> array_size >> queries;

    BIT<long long, true> fenwick_tree(array_size);
    for (int i = 0; i < queries; ++i)
    {
        string operation;
        cin >> operation;
        if (operation == "add")
        {
            int index, addition;
            cin >> index >> addition;
            fenwick_tree.updateTree(index, addition);
        }
        else if (operation == "query")
        {
            int left_bound, right_bound;
            cin >> left_bound >> right_bound;
            cout << fenwick_tree.queryRange(left_bound, right_bound) << "\n";
        }
        else if (operation == "find")
        {
            int target_sum;
            cin >> target_sum;
            cout << fenwick_tree.findFirstPrefix(target_sum) << "\n";
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}