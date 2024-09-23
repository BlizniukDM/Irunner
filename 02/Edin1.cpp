#include <iostream>
#include <vector>

using namespace std;

const int NUMBER = 1000000007;

void Filling(int N, int K, vector<vector<int>>& ma);

int main()
{
    int N, K;
    cin >> N >> K;
    vector<vector<int>> ma(N + 1, vector<int>(K + 1, 0));

    Filling(N, K, ma);
    cout << ma[N][K] << endl;

    return 0;
}

void Filling(int N, int K, vector<vector<int>>& ma)
{
    ma[0][0] = 1;
    for (int n = 1; n <= N; ++n)
    {
        for (int k = 0; k <= K; ++k) 
        {
            ma[n][k] = ma[n - 1][k];
            if (k > 0) 
            {
                ma[n][k] = (ma[n][k] + ma[n - 1][k - 1]) % NUMBER;
            }
        }
    }
}