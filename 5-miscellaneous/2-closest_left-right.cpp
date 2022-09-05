#include <bits/stdc++.h>
using namespace std;

template <typename number_type, typename number_type_compare>
vector<int> getClosestLeft(const vector<number_type> &values, number_type_compare &&compare)
{
    int array_size = (int)values.size();

    vector<int> indices_stack;
    vector<int> closest_left(array_size);
    for (int i = 0; i < array_size; ++i)
    {
        while (!indices_stack.empty() && !compare(values[indices_stack.back()], values[i]))
        {
            indices_stack.pop_back();
        }
        closest_left[i] = (indices_stack.empty() ? -1 : indices_stack.back());
        indices_stack.emplace_back(i);
    }
    return closest_left;
}

template <typename number_type, typename number_type_compare>
vector<int> getClosestRight(const vector<number_type> &values, number_type_compare &&compare)
{
    int array_size = (int)values.size();

    vector<int> indices_stack;
    vector<int> closest_right(array_size);
    for (int i = array_size - 1; i >= 0; --i)
    {
        while (!indices_stack.empty() && !compare(values[indices_stack.back()], values[i]))
        {
            indices_stack.pop_back();
        }
        closest_right[i] = (indices_stack.empty() ? array_size : indices_stack.back());
        indices_stack.emplace_back(i);
    }
    return closest_right;
}

int main()
{
    int array_size;
    cin >> array_size;

    vector<int> initial_array(array_size);
    for (int i = 0; i < array_size; ++i)
    {
        cin >> initial_array[i];
    }

    vector<int> to_left = getClosestLeft(initial_array, less<int>{});
    for (int i = 0; i < array_size; ++i)
    {
        cout << to_left[i] << " \n"[i == array_size - 1];
    }

    vector<int> to_right = getClosestRight(initial_array, less<int>{});
    for (int i = 0; i < array_size; ++i)
    {
        cout << to_right[i] << " \n"[i == array_size - 1];
    }
    return 0;
}