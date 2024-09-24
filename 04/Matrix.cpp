#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int min_ma(const vector<int>& dimensions, int s); 

int main() 
{
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) 
    {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    int s;
    inputFile >> s;

    vector<int> dimensions(s + 1);
    for (int i = 0; i < s; ++i) {
        inputFile >> dimensions[i] >> dimensions[i + 1];
    }

    int result = min_ma(dimensions, s);

    outputFile << result << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}


int min_ma(const vector<int>& dimensions, int s)
{
    vector<vector<int>> dp(s, vector<int>(s, 0));

    for (int len = 2; len <= s; ++len) 
    {
        for (int i = 0; i < s - len + 1; ++i) 
        {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[0][s - 1];
}