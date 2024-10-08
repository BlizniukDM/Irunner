/*
1)Сортируем все купюры (как покупателя, так и продавца) по возрастанию.
Это позволяет нам последовательно проверять, какие суммы можно вернуть
с помощью имеющихся купюр.
2)Переменная 𝑆 отслеживает максимальную сдачу, которую можно вернуть, 
используя часть или все доступные купюры. Идея состоит в том, что если 
мы можем вернуть любую сумму от 1 до 𝑆, но не можем вернуть сумму (S+1),
то эта сумма и будет наибольшей непредставимой (недоступной) суммой.
3)Итерация по купюрам. Мы проходим по отсортированным купюрам и, 
если очередная купюра a𝑖 меньше или равна (S+1), обновляем значение S.
Это означает, что мы можем вернуть сумму от 1 до (S + a𝑖). Если встречаем
купюру, которая больше (S+1), то (S+1) — это сумма, которую невозможно вернуть.
4)Сравнение с общей суммой. После того, как определили максимальную сдачу S,
проверяем, можно ли вернуть сдачу на любую возможную покупку (т.е.
S больше или равен суммарной стоимости всех купюр покупателя).
Если да, выводим "YES", иначе — "NO" и наибольшую непредставимую стоимость.
*/

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

    int S = 0;

    for (int i = 0; i < allBills.size(); ++i) {
        if (allBills[i] > S + 1) {
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
        outputFile << totalMoney - (S + 1) << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
