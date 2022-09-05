#include <bits/stdc++.h>
using namespace std;

vector<int> createManacher(const string &pattern)
{
    int pattern_size = (int)pattern.size();
    string word = string(2 * pattern_size + 1, '$');
    for (int i = 0; i < pattern_size; ++i)
    {
        word[2 * i + 1] = pattern[i];
    }

    int string_size = (int)word.size();
    vector<int> radius(string_size, 0);

    int location = 0;
    for (int center = 1; center < string_size; ++center)
    {
        if (center <= location + radius[location])
        {
            radius[center] = min(radius[location - (center - location)],
                                 location + radius[location] - center);
        }

        while (0 <= center - radius[center] && center + radius[center] < string_size &&
               word[center - radius[center]] == word[center + radius[center]])
        {
            ++radius[center];
        }

        if (center + radius[center] > location + radius[location])
        {
            location = center;
        }
    }
    return radius;
}

bool isPalindrome(int left_bound, int right_bound, const vector<int> &manacher)
{
    return manacher[left_bound + right_bound + 1] >= (right_bound - left_bound + 1);
}

int main()
{
}