#include <bits/stdc++.h>
using namespace std;

template <typename number_type>
vector<number_type> kmpArray(const vector<number_type> &initial_array)
{
    int array_size = (int)initial_array.size();
    vector<int> prefix_function(array_size, 0);
    for (int i = 1; i < array_size; ++i)
    {
        int j = prefix_function[i - 1];
        while (j > 0 && initial_array[i] != initial_array[j])
        {
            j = prefix_function[j - 1];
        }

        if (initial_array[i] == initial_array[j])
        {
            ++j;
        }
        prefix_function[i] = j;
    }
    return prefix_function;
}

int main()
{
    int first_array_size, second_array_size;
    cin >> first_array_size >> second_array_size;

    vector<int> first_array(first_array_size);
    for (int i = 0; i < first_array_size; ++i)
    {
        cin >> first_array[i];
    }

    vector<int> second_array(second_array_size);
    for (int i = 0; i < second_array_size; ++i)
    {
        cin >> second_array[i];
    }

    
    return 0;
}