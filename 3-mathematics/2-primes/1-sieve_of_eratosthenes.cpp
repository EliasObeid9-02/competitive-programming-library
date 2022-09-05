#include <bits/stdc++.h>
using namespace std;

const int MAXA = 200'000;

vector<bool> is_prime;
vector<int> smallest_factor, primes;

void sieve()
{
    if (!primes.empty())
    {
        return;
    }
    is_prime.resize(MAXA + 1, true);
    smallest_factor.resize(MAXA + 1, 0);

    is_prime[0] = is_prime[1] = false;
    smallest_factor[0] = smallest_factor[1] = 1;
    for (int value = 2; value <= MAXA; ++value)
    {
        if (is_prime[value])
        {
            primes.emplace_back(value);
            smallest_factor[value] = value;
            for (int k = 2; k * value <= MAXA; ++k)
            {
                if (is_prime[k * value])
                {
                    is_prime[k * value] = false;
                    smallest_factor[k * value] = value;
                }
            }
        }
    }
}

vector<pair<int, int>> factorize(int value)
{
    if (primes.empty())
    {
        sieve();
    }

    vector<pair<int, int>> factors;
    while (value != 1)
    {
        int prime = smallest_factor[value];
        factors.emplace_back(prime, 0);
        while (value % prime == 0)
        {
            value /= prime;
            ++factors.back().second;
        }
    }
    return factors;
}

int main()
{
    int array_size;
    cin >> array_size;

    for (int i = 0; i < array_size; ++i)
    {
        int value;
        cin >> value;

        vector<pair<int, int>> factors = factorize(value);
        for (const auto &[prime_value, prime_frequency] : factors)
        {
            for (int c = 0; c < prime_frequency; ++c)
            {
                cout << prime_value << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}