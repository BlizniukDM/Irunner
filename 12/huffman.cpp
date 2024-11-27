#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{   
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);

    int n;
    cin >> n;
    vector<long long> freq(n);

    for (int i = 0; i < n; ++i) 
    {
        cin >> freq[i];
    }

    sort(freq.begin(), freq.end());

    long long totalLength = 0;

    while (freq.size() > 1) {
        long long first = freq[0];
        long long second = freq[1];

        freq.erase(freq.begin());
        freq.erase(freq.begin());

        long long combined = first + second;
        totalLength += combined;

        auto it = lower_bound(freq.begin(), freq.end(), combined);
        freq.insert(it, combined);
    }

    cout << totalLength << endl;

    return 0;
}
