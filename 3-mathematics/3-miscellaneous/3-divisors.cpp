#include <bits/stdc++.h>
using namespace std;

template <typename number_type>
vector<number_type> getDivisors(number_type value)
{
    vector<number_type> small_divisors;
    vector<number_type> large_divisors;
    for (number_type divisor = 1; divisor * divisor <= value; ++divisor)
    {
        if (value % divisor == 0)
        {
            small_divisors.emplace_back(divisor);
            if (value / divisor != divisor)
            {
                large_divisors.emplace_back(value / divisor);
            }
        }
    }
    reverse(large_divisors.begin(), large_divisors.end());
    small_divisors.insert(small_divisors.end(),
                          large_divisors.begin(),
                          large_divisors.end());
    return small_divisors;
}

int main()
{
    long long value;
    cin >> value;

    for (long long divisor : getDivisors(value))
    {
        cout << divisor << " \n"[divisor == value];
    }
    return 0;
}