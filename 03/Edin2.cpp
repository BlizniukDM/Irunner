#include <iostream>
#include <vector>

using namespace std;

const int NUMBER = 1000000007;

void Filling(int N, int K, vector<int>& ma);

int main()
{
    int N, K;
    cin >> N >> K;
    vector<int> ma(K + 1, 0);

    Filling(N, K, ma);
    cout << ma[K] << endl;

    return 0;
}

void Filling(int N, int K, vector<int>& ma)
{
    ma[0] = 1;
    for (int n = 1; n <= N; ++n)
    {
        for (int k = K; k > 0; --k)
        {
            ma[k] = (ma[k] + ma[k - 1]) % NUMBER;
        }
    }
}