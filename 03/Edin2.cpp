// C(n,k) = n! / (k!(n - k)!)

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;
vector<long long> fact;
vector<long long> fact2;

long long bin_pow(long long a, long long b, long long mod);
long long binomial(int n, int k, int mod);
void precompute_factorials(int n, int mod);

int main() 
{
    int N, K;
    cin >> N >> K;
    precompute_factorials(N, MOD);
    cout << binomial(N, K, MOD) << endl;

    return 0;
}

long long bin_pow(long long a, long long b, long long mod) 
{
    long long res = 1;
    while (b > 0) 
    {
        if (b % 2 == 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b /= 2;
    }
    return res;
}

long long binomial(int n, int k, int mod) 
{
    if (k > n) return 0;
    return fact[n] * fact2[k] % mod * fact2[n - k] % mod;
}

void precompute_factorials(int n, int mod) 
{
    fact.resize(n + 1);
    fact2.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) 
    {
        fact[i] = fact[i - 1] * i % mod;
    }
    fact2[n] = bin_pow(fact[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; --i) 
    {
        fact2[i] = fact2[i + 1] * (i + 1) % mod;
    }
}