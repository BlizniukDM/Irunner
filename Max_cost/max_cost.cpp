#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
ifstream inputFile("input.txt");
ofstream outputFile("output.txt");

if (!inputFile.is_open() || !outputFile.is_open()) {
    cerr << "Ошибка открытия файлов!" << endl;
    return 1;
}

int n, m;
inputFile >> n >> m;

vector<int> buyerBills(n);
vector<int> sellerBills(m);

for (int i = 0; i < n; ++i) {
    inputFile >> buyerBills[i];
}

for (int i = 0; i < m; ++i) {
    inputFile >> sellerBills[i];
}

vector<int> allBills = buyerBills;
allBills.insert(allBills.end(), sellerBills.begin(), sellerBills.end());

sort(allBills.begin(), allBills.end());

int S = 1;

for (int i = 0; i < allBills.size(); ++i) {
    if (allBills[i] > S) {
        break;
    }
    S += allBills[i];
}

int totalMoney = 0;
for (int bill : buyerBills) {
    totalMoney += bill;
}

if (S >= totalMoney) {
    outputFile << "YES" << endl;
} else {
    outputFile << "NO" << endl;
    outputFile << totalMoney - S << endl;
}

inputFile.close();
outputFile.close();

return 0;
}
