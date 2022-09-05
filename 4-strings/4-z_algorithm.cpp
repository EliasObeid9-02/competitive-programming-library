#include <bits/stdc++.h>
using namespace std;

vector<int> ZAlgorithm(const string &initial_string)
{
    int string_size = (int)initial_string.size();
    vector<int> z_algorithm(string_size, 0);
    for (int i = 1, l = 0, r = 0; i < string_size; ++i)
    {
        if (i <= r)
        {
            z_algorithm[i] = min(r - i + 1, z_algorithm[i - l]);
        }

        while (i + z_algorithm[i] < string_size && initial_string[z_algorithm[i]] == initial_string[i + z_algorithm([i])])
        {
            ++z_algorithm[i];
        }

        if (i + z_algorithm[i] > r)
        {
            l = i;
            r = i + z_algorithm[i] - 1;
        }
    }
    return z_algorithm;
}

int main()
{
    return 0;
}