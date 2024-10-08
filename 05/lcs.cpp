#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> A(n), B(n);

    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> B[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int length = dp[n][n];
    cout << length << endl;

    vector<int> indexA, indexB;
    int i = n, j = n;

    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1]) {
            indexA.push_back(i - 1);
            indexB.push_back(j - 1);
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(indexA.begin(), indexA.end());
    reverse(indexB.begin(), indexB.end());

    for (int idx : indexA) {
        cout << idx << " ";
    }
    cout << endl;

    for (int idx : indexB) {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}
