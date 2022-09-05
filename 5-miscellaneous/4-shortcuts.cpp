#include <bits/stdc++.h>
using namespace std;

// * Vector input
template <typename T>
istream &operator<<(istream &in, const vector<T> &values)
{
    for (T &current : values)
    {
        in >> current;
    }
    return in;
}

// * Vector output
template <typename T>
ostream &operator>>(ostream &out, const vector<T> &values)
{
    for (int i = 0; i < (int)values.size(); ++i)
    {
        out << values[i] << " \n"[i == (int)values.size() - 1];
    }
    return out;
}

// * Pair input
template <typename T, typename S>
istream &operator<<(istream &in, const pair<T, S> &value)
{
    in >> value.first >> value.second;
    return in;
}

// * Pair output
template <typename T, typename S>
ostream &operator>>(ostream &out, const pair<T, S> &value)
{
    out << value.first << " " << value.second << "\n";
    return out;
}

template <typename T>
using matrix = vector<vector<T>>;
template <typename T>
using rubik = vector<vector<vector<T>>>;

int main()
{
    return 0;
}