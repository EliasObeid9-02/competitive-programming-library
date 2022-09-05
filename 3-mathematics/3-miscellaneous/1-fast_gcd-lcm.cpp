#include <bits/stdc++.h>
using namespace std;

template <typename number_type>
number_type GCD(number_type first, number_type second)
{
    return (first == number_type{} ? second : GCD(second % first, first));
}

template <typename number_type>
number_type LCM(number_type first, number_type second)
{
    return first / GCD(first, second) * second;
}

int main()
{
    int queries;
    cin >> queries;

    for (int i = 0; i < queries; ++i)
    {
        string operation;
        int first, second;
        cin >> operation >> first >> second;
        if (operation == "gcd")
        {
            cout << GCD(first, second) << "\n";
        }
        else if (operation == "lcm")
        {
            cout << LCM(first, second) << "\n";
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}