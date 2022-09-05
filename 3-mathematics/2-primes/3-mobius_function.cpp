#include <bits/stdc++.h>
using namespace std;

const int MAXA = 200'000;

vector<bool> is_prime;
vector<int> mobius, primes;

void sieveMobius()
{
    if (!primes.empty())
    {
        return;
    }

    mobius.resize(MAXA + 1, 1);
    is_prime.resize(MAXA + 1, true);

    is_prime[0] = is_prime[1] = false;
    for (int value = 2; value <= MAXA; ++value)
    {
        if (is_prime[value])
        {
            mobius[value] = -1;
            primes.emplace_back(value);
        }

        for (int p : primes)
        {
            if (p * value > MAXA)
            {
                break;
            }
            mobius[p * value] = (value % p == 0 ? 0 : mobius[p] * mobius[value]);
            is_prime[p * value] = false;
        }
    }
}

int main()
{
    int array_size;
    cin >> array_size;
    sieveMobius();

    for (int i = 0; i < array_size; ++i)
    {
        int value;
        cin >> value;
        cout << mobius[value] << " \n"[i == array_size - 1];
    }
    return 0;
}