#include <bits/stdc++.h>
using namespace std;

template <typename number_type, bool one_indexing_mode = false>
class SparseTable
{
private:
    static int getHighestBit(int value)
    {
        return (value == 0 ? -1 : 31 - __builtin_clz(value));
    }

    int table_size, table_levels;
    vector<vector<number_type>> table_values;

    number_type combineCells(number_type first_cell, number_type second_cell)
    {
        return (first_cell + second_cell);
    }

public:
    SparseTable() {}
    SparseTable(int array_size, const vector<number_type> &initial_array)
        : table_size{array_size + (int)one_indexing_mode},
          table_levels{getHighestBit(array_size) + 1},
          table_values(table_levels, vector<number_type>(table_size))
    {
        table_values[0] = initial_array;
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

    number_type queryRange(int left_bound, int right_bound)
    {
        number_type range_sum{};
        for (int level = table_levels - 1; level >= 0; --level)
        {
            if (left_bound + (1 << level) <= right_bound + 1)
            {
                range_sum = combineCells(range_sum, table_values[level][left_bound]);
                left_bound += (1 << level);
            }
        }
        return range_sum;
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

    SparseTable<long long> sparse_table(array_size, initial_array);
    for (int i = 0; i < queries; ++i)
    {
        int left_bound, right_bound;
        cin >> left_bound >> right_bound;
        cout << sparse_table.queryRange(left_bound, right_bound) << "\n";
    }
    return 0;
}