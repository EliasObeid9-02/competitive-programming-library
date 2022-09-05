#include <bits/stdc++.h>
using namespace std;

const int MAXA = 200'000;

vector<int> phi;

void sievePhi()
{
    if (!phi.empty())
    {
        return;
    }

    phi.resize(MAXA + 1);
    iota(phi.begin(), phi.end(), 0);

    for (int value = 2; value <= MAXA; ++value)
    {
        if (phi[value] == value)
        {
            for (int k = 1; k * value <= MAXA; ++k)
            {
                phi[k * value] -= phi[k * value] / value;
            }
        }
    }
}

int getPhi(int value)
{
    if (phi.empty())
    {
        sievePhi();
    }

    if (value <= MAXA)
    {
        return phi[value];
    }

    int result = value;
    for (int divisor = 2; divisor * divisor <= value; ++divisor)
    {
        if (value % divisor == 0)
        {
            while (value % divisor == 0)
            {
                value /= divisor;
            }
            result -= result / divisor;
        }
    }

    if (value > 1)
    {
        result -= result / value;
    }
    return result;
}

int main()
{
    int array_size;
    cin >> array_size;

    for (int i = 0; i < array_size; ++i)
    {
        int value;
        cin >> value;
        cout << getPhi(value) << "\n";
    }
    return 0;
}