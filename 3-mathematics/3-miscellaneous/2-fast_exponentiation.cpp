#include <bits/stdc++.h>
using namespace std;

const int MOD = 998'244'353;

template <typename number_type>
number_type fastPower(number_type N, number_type K)
{
    number_type result = 1;
    while (K > 0)
    {
        if (K & 1)
        {
            result = (result * N);
        }
        N = (N * N);
        K >>= 1;
    }
    return result;
}

template <typename number_type>
number_type fastModularPower(number_type N, number_type K)
{
    number_type result = 1;
    while (K > 0)
    {
        if (K & 1)
        {
            result = (result * N) % MOD;
        }
        N = (N * N) % MOD;
        K >>= 1;
    }
    return result;
}

int main()
{
    int N, K;
    cin >> N >> K;
    cout << fastPower(N, K) << "\n";
    cout << fastModularPower(N, K) << "\n";
    return 0;
}