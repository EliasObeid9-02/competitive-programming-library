#include <bits/stdc++.h>
using namespace std;

const int MOD = 998'244'353;

template <const int modulo>
struct modular_int
{
	int value;
	modular_int(int v) : modular_int(static_cast<long long>(v)) {}
	modular_int(long long v = 0)
	{
		if (v < 0)
		{
			v = v % modulo + modulo;
		}

		if (v >= modulo)
		{
			v = v % modulo;
		}
		value = static_cast<int>(v);
	}

	explicit operator int() const { return value; }
	explicit operator unsigned() const { return value; }
	explicit operator long long() const { return value; }
	explicit operator unsigned long long() const { return value; }
	explicit operator double() const { return value; }
	explicit operator long double() const { return value; }

	modular_int &operator+=(const modular_int &other)
	{
		value = (value + other.value) % modulo;
		return *this;
	}

	modular_int &operator-=(const modular_int &other)
	{
		value = ((value - other.value) % modulo + modulo) % modulo;
		return *this;
	}

	modular_int &operator*=(const modular_int &other)
	{
		value = (1LL * value * other.value) % modulo;
		return *this;
	}

	modular_int &operator/=(const modular_int &other)
	{
		*this *= other.inv();
		return *this;
	}

	friend modular_int operator+(const modular_int &a, const modular_int &b) { return modular_int(a) += b; }
	friend modular_int operator-(const modular_int &a, const modular_int &b) { return modular_int(a) -= b; }
	friend modular_int operator*(const modular_int &a, const modular_int &b) { return modular_int(a) *= b; }
	friend modular_int operator/(const modular_int &a, const modular_int &b) { return modular_int(a) /= b; }

	modular_int &operator++()
	{
		value = (value == modulo - 1 ? 0 : value + 1);
		return *this;
	}

	modular_int &operator--()
	{
		value = (value == 0 ? MOD - 1 : value - 1);
		return *this;
	}

	modular_int operator++(int)
	{
		modular_int before = *this;
		++*this;
		return before;
	}
	modular_int operator--(int)
	{
		modular_int before = *this;
		--*this;
		return before;
	}

	modular_int operator-() const
	{
		return (value == 0 ? 0 : MOD - value);
	}

	friend bool operator==(const modular_int &a, const modular_int &b) { return a.value == b.value; }
	friend bool operator!=(const modular_int &a, const modular_int &b) { return a.value != b.value; }
	friend bool operator<(const modular_int &a, const modular_int &b) { return a.value < b.value; }
	friend bool operator>(const modular_int &a, const modular_int &b) { return a.value > b.value; }
	friend bool operator<=(const modular_int &a, const modular_int &b) { return a.value <= b.value; }
	friend bool operator>=(const modular_int &a, const modular_int &b) { return a.value >= b.value; }

	friend ostream &operator<<(ostream &os, const modular_int &m)
	{
		return os << m.value;
	}

	static const int SAVE_INV = int(1e6) + 5;
	static modular_int save_inv[SAVE_INV];

	static void prepare_inv()
	{
		save_inv[0] = 0;
		save_inv[1] = 1;
		for (int i = 2; i < SAVE_INV; i++)
		{
			save_inv[i] = save_inv[modulo % i] * (modulo - modulo / i);
		}
	}

	modular_int inv() const
	{
		if (save_inv[1] == 0)
		{
			prepare_inv();
		}

		if (value < SAVE_INV)
		{
			return save_inv[value];
		}
		else
		{
			int v = value;
			modular_int product = 1;
			while (v >= SAVE_INV)
			{
				product *= MOD - MOD / v;
				v = MOD % v;
			}
			return product * save_inv[v];
		}
	}

	modular_int pow(long long P) const
	{
		if (P < 0)
		{
			return inv().pow(-P);
		}
		else
		{

			modular_int result = 1;
			modular_int base = *this;
			while (P > 0)
			{
				if (P & 1)
				{
					result *= base;
				}
				P >>= 1;

				if (P > 0)
				{
					base *= base;
				}
			}
			return result;
		}
	}
};

template <const int modulo>
modular_int<modulo> modular_int<modulo>::save_inv[modular_int<modulo>::SAVE_INV];

using mod_int = modular_int<MOD>;

const int MAXA = 200'000;
vector<mod_int> fact, inv_fact;

void preCalcFactorials(int A = MAXA)
{
	if (!fact.empty())
	{
		return;
	}
	fact.resize(A + 1, 1);
	inv_fact.resize(A + 1, 1);

	for (int i = 2; i <= A; ++i)
	{
		fact[i] = fact[i - 1] * i;
	}

	inv_fact[A] = fact[A].inv();
	for (int i = A - 1; i >= 1; --i)
	{
		inv_fact[i] = inv_fact[i + 1] * (i + 1);
	}
}

mod_int NCR(int N, int R)
{
	if (fact.empty())
	{
		preCalcFactorials();
	}

	if (N < R)
	{
		return 0;
	}
	else
	{
		return fact[N] * inv_fact[N - R] * inv_fact[R];
	}
}

mod_int PNR(int N, int R)
{
	if (fact.empty())
	{
		preCalcFactorials();
	}

	if (N < R)
	{
		return 0;
	}
	else
	{
		return fact[N] * inv_fact[N - R];
	}
}

int main()
{
	int N, R;
	cin >> N >> R;
	cout << NCR(N, R) << " " << PNR(N, R) << "\n";
	return 0;
}