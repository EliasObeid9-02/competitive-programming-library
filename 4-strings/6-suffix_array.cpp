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

class SuffixArray
{
private:
    string word;
    int word_size;
    vector<int> rank, order, lcp;
    RMQ<int, false, false> minimum_lcp;

    void generateRanks(int level)
    {
        vector<int> new_rank(word_size);
        new_rank[order[0]] = 0;
        for (int i = 1; i < word_size; ++i)
        {
            int old_x = order[i - 1], old_y = (order[i - 1] + (1 << level) + word_size) % word_size;
            int new_x = order[i - 0], new_y = (order[i - 0] + (1 << level) + word_size) % word_size;
            pair<int, int> old_substring = make_pair(rank[old_x], rank[old_y]);
            pair<int, int> new_substring = make_pair(rank[new_x], rank[new_y]);
            new_rank[order[i]] = new_rank[order[i - 1]] + (old_substring == new_substring ? 0 : 1);
        }
        rank.swap(new_rank);
    }

    void countSort()
    {
        vector<int> frequency(word_size), new_order(word_size);
        for (int current_rank : rank)
        {
            ++frequency[current_rank];
        }

        vector<int> positions(word_size);
        for (int i = 1; i < word_size; ++i)
        {
            positions[i] = positions[i - 1] + frequency[i - 1];
        }

        for (int i = 0; i < word_size; ++i)
        {
            int suffix_start = order[i];
            int block_index = rank[suffix_start];
            new_order[positions[block_index]] = suffix_start;
            ++positions[block_index];
        }
        order.swap(new_order);
    }

    void buildArray()
    {
        rank.resize(word_size);
        order.resize(word_size);

        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j)
             { return make_pair(word[i], i) < make_pair(word[j], j); });

        rank[order[0]] = 0;
        for (int i = 1; i < word_size; ++i)
        {
            rank[order[i]] = rank[order[i - 1]] + (word[order[i]] == word[order[i - 1]] ? 0 : 1);
        }

        for (int level = 0; (1 << level) < word_size; ++level)
        {
            for (int i = 0; i < word_size; ++i)
            {
                order[i] = (order[i] - (1 << level) + word_size) % word_size;
            }
            countSort();
            generateRanks(level);
        }
    }

    void buildLCP()
    {
        lcp.resize(word_size - 1);
        int common_prefix_length = 0;
        for (int i = 0; i < word_size - 1; ++i)
        {
            int suffix_order = rank[i];
            int suffix_start = order[suffix_order - 1];
            while (word[i + common_prefix_length] == word[suffix_start + common_prefix_length])
            {
                ++common_prefix_length;
            }
            lcp[suffix_order - 1] = common_prefix_length;
            common_prefix_length = max(common_prefix_length - 1, 0);
        }
        minimum_lcp = RMQ<int, false, false>(word_size - 1, lcp);
    }

    template <typename string_compare>
    int getFirstSuffix(const string &pattern, string_compare &&compare)
    {
        int pattern_size = (int)pattern.size();

        int first_suffix = word_size;
        int low = 0, high = word_size - 1;
        while (low <= high)
        {
            int middle = low + (high - low) / 2;
            int suffix_start = order[middle];

            string current_suffix = "";
            if (suffix_start + pattern_size <= word_size)
            {
                current_suffix = word.substr(suffix_start, pattern_size);
            }
            else
            {
                current_suffix = word.substr(suffix_start, word_size - suffix_start) +
                                 word.substr(0, pattern_size - (word_size - suffix_start));
            }

            if (compare(current_suffix, pattern))
            {
                first_suffix = middle;
                high = middle - 1;
            }
            else
            {
                low = middle + 1;
            }
        }
        return first_suffix;
    }

public:
    SuffixArray(const string &_word) : word{_word + '$'}, word_size{(int)word.size()}
    {
        buildArray();
        buildLCP();
    }

    int getOrder(int index)
    {
        return order[index];
    }

    int getSubstringCount(const string &pattern)
    {
        return getFirstSuffix(pattern, greater<string>{}) -
               getFirstSuffix(pattern, greater_equal<string>{});
    }

    int getLCP(int first_suffix, int second_suffix)
    {
        int first_start = rank[first_suffix];
        int second_start = rank[second_suffix];

        if (first_start > second_start)
        {
            swap(first_start, second_start);
        }

        if (first_start == second_start)
        {
            return word_size - 1 - first_suffix;
        }
        else
        {
            return minimum_lcp.queryRange(first_start, second_start - 1);
        }
    }

    long long getDistinctCount()
    {
        long long distinct_count = (long long)word_size * (word_size - 1) / 2;
        return distinct_count - accumulate(lcp.begin(), lcp.end(), 0LL);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string word;
    cin >> word;

    int string_size = (int)word.size();
    SuffixArray suffix_array(word);
    for (int i = 0; i <= string_size; ++i)
    {
        cout << suffix_array.getOrder(i) << " \n"[i == string_size];
    }

    for (int i = 0; i < string_size; ++i)
    {
        int first_suffix = suffix_array.getOrder(i);
        int second_suffix = suffix_array.getOrder(i + 1);
        cout << suffix_array.getLCP(first_suffix, second_suffix) << " \n"[i == string_size - 1];
    }
    return 0;
}