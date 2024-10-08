#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int findLISLength(const vector<int>& sequence);

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Не удалось открыть файлы." << endl;
        return 1;
    }

    int n;
    inputFile >> n;
    vector<int> sequence(n);

    for (int i = 0; i < n; ++i) {
        inputFile >> sequence[i]; 
    }

    int lisLength = findLISLength(sequence);

    outputFile << lisLength << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}

int findLISLength(const vector<int>& sequence) {
    vector<int> lis;
    for (int i = 0; i < sequence.size(); ++i) {
        int num = sequence[i];

        auto it = lower_bound(lis.begin(), lis.end(), num);
        if (it == lis.end()) {
            lis.push_back(num);
        } else {
            *it = num;
        }
    }

    return lis.size();
}
