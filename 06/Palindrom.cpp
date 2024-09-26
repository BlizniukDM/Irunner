#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void findPalindrome(const string& s, int& palindromeLength, string& palindrome);

int main() 
{
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) 
    {
        cerr << "Ошибка открытия файла" << endl;
        return 1;
    }

    string s;
    inputFile >> s;

    int palindromeLength;
    string palindrome;

    findPalindrome(s, palindromeLength, palindrome);

    outputFile << palindromeLength << endl;
    outputFile << palindrome << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}

void findPalindrome(const string& s, int& palindromeLength, string& palindrome) 
{
    int n = s.size();
    
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int length = 2; length <= n; ++length) 
    {
        for (int i = 0; i <= n - length; ++i) 
        {
            int j = i + length - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1];  
            } else {
                dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
            }
        }
    }

    palindrome = string(n - dp[0][n - 1], ' ');
    palindromeLength = palindrome.size();
    
    int left = 0, right = palindrome.size() - 1;
    int i = 0, j = n - 1;

    while (i <= j) 
    {
        if (s[i] == s[j]) 
        {
            palindrome[left++] = s[i];
            palindrome[right--] = s[j];
            i++;
            j--;
        } else if (dp[i + 1][j] < dp[i][j - 1]) 
        {
            i++; 
        } else 
        {
            j--;
        }
    }
}