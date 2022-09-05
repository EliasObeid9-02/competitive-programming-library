#include <bits/stdc++.h>
using namespace std;

vector<pair<char, int>> stringCompression(const string &word)
{
    int string_size = (int)word.size();
    vector<pair<char, int>> compressed_string;
    for (int i = 0; i < string_size; ++i)
    {
        if (compressed_string.empty() || compressed_string.back().first != word[i])
        {
            compressed_string.emplace_back(word[i], 1);
        }
        else
        {
            ++compressed_string.back().second;
        }
    }
    return compressed_string;
}

int main()
{
    string word;
    cin >> word;

    for (const auto &[character, counts] : stringCompression(word))
    {
        cout << character << " " << counts << "\n";
    }
    return 0;
}