#include <bits/stdc++.h>
using namespace std;

template <typename number_type>
void compressArray(vector<number_type> &initial_array)
{
    int array_size = (int)initial_array.size();
    vector<number_type> values = initial_array;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    for (int i = 0; i < array_size; ++i)
    {
        initial_array[i] = lower_bound(values.begin(), values.end(), initial_array[i]) - values.begin();
    }
}

int main()
{
    int array_size;
    cin >> array_size;

    vector<int> coordinates(array_size);
    for (int i = 0; i < array_size; ++i)
    {
        cin >> coordinates[i];
    }
    compressArray(coordinates);

    for (int i = 0; i < array_size; ++i)
    {
        cout << coordinates[i] << " \n"[i == array_size - 1];
    }
    return 0;
}