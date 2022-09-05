#include <bits/stdc++.h>
using namespace std;

vector<int> kmpString(const string &initial_string)
{
    int string_size = (int)initial_string.size();
    vector<int> prefix_function(string_size);
    for (int i = 1; i < string_size; ++i)
    {
        int j = prefix_function[i - 1];
        while (j > 0 && initial_string[i] != initial_string[j])
        {
            j = prefix_function[j - 1];
        }

        if (initial_string[i] == initial_string[j])
        {
            ++j;
        }
        prefix_function[i] = j;
    }
    return prefix_function;
}

int main()
{
    // Given two strings A and B count the number of occurrences of B in A
    string first_string, second_string;
    cin >> first_string >> second_string;

    string word = second_string + '#' + first_string;
    vector<int> prefix_function = kmpString(word);

    int occurrences = 0;
    for (int i = 0; i < (int)word.size(); ++i)
    {
        if (prefix_function[i] == (int)second_string.size())
        {
            ++occurrences;
        }
    }
    cout << occurrences << "\n";
    return 0;
}