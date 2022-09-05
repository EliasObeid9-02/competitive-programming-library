#include <bits/stdc++.h>
using namespace std;

template <typename number_type, bool one_indexing_mode = false, bool maximum_mode = false>
class RMQ
{
private:
    static int getHighestBit(int value)
    {
        return (value == 0 ? -1 : 31 - __builtin_clz(value));
    }

    int table_size, table_levels;
    vector<number_type> values;
    vector<vector<int>> table_values;

    int combineCells(int first_index, int second_index)
    {
        return (maximum_mode ? (values[first_index] > values[second_index] ? first_index : second_index)
                             : (values[first_index] < values[second_index] ? first_index : second_index));
    }

public:
    RMQ() {}
    RMQ(int array_size, const vector<number_type> &initial_array)
        : table_size{array_size + (int)one_indexing_mode},
          table_levels{getHighestBit(array_size) + 1},
          values{initial_array},
          table_values(table_levels, vector<int>(table_size))
    {
        iota(table_values[0].begin(), table_values[0].end(), 0);
        buildTable();
    }

    void buildTable()
    {
        for (int level = 1; level < table_levels; ++level)
        {
            for (int i = (int)one_indexing_mode; i + (1 << level) <= table_size; ++i)
            {
                table_values[level][i] = combineCells(table_values[level - 1][i],
                                                      table_values[level - 1][i + (1 << (level - 1))]);
            }
        }
    }

    int queryIndex(int left_bound, int right_bound)
    {
        int level = getHighestBit(right_bound - left_bound + 1);
        return combineCells(table_values[level][left_bound],
                            table_values[level][right_bound - (1 << level) + 1]);
    }

    number_type queryRange(int left_bound, int right_bound)
    {
        return values[queryIndex(left_bound, right_bound)];
    }
};

int main()
{
    int array_size, queries;
    cin >> array_size >> queries;

    vector<long long> initial_array(array_size);
    for (int i = 0; i < array_size; ++i)
    {
        cin >> initial_array[i];
    }

    RMQ<long long> range_minimums(array_size, initial_array);
    for (int i = 0; i < queries; ++i)
    {
        int left_bound, right_bound;
        cin >> left_bound >> right_bound;
        cout << range_minimums.queryRange(left_bound, right_bound) << "\n";
    }
    return 0;
}