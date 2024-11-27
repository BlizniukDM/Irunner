#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class RangeManager {
private:
    unordered_map<int, long long> segmentTree;
    int arraySize;

    long long getValue(int currentNode);
    void initialize(const vector<int>& arr, int currentNode, int segmentStart, int segmentEnd);
    void modify(int currentNode, int segmentStart, int segmentEnd, int index, int value);
    long long calculateSum(int currentNode, int segmentStart, int segmentEnd, int queryStart, int queryEnd);

public:
    RangeManager(const vector<int>& arr);
    void addValue(int index, int value);
    long long querySum(int left, int right);
};

int main() {
    int arrayLength;
    cin >> arrayLength;

    vector<int> inputArray(arrayLength);
    for (int i = 0; i < arrayLength; ++i) {
        cin >> inputArray[i];
    }

    int numberOfQueries;
    cin >> numberOfQueries;

    RangeManager manager(inputArray);

    for (int i = 0; i < numberOfQueries; ++i) {
        string command;
        cin >> command;
        if (command == "Add") {
            int index, value;
            cin >> index >> value;
            manager.addValue(index, value);
        } else if (command == "FindSum") {
            int left, right;
            cin >> left >> right;
            cout << manager.querySum(left, right) << "\n";
        }
    }

    return 0;
}

RangeManager::RangeManager(const vector<int>& arr) {
    arraySize = arr.size();
    initialize(arr, 0, 0, arraySize - 1);
}

long long RangeManager::getValue(int currentNode) {
    if (segmentTree.find(currentNode) == segmentTree.end()) {
        return 0;
    }
    return segmentTree[currentNode];
}

void RangeManager::initialize(const vector<int>& arr, int currentNode, int segmentStart, int segmentEnd) {
    if (segmentStart == segmentEnd) {
        segmentTree[currentNode] = arr[segmentStart];
    } else {
        int middle = (segmentStart + segmentEnd) / 2;
        initialize(arr, 2 * currentNode + 1, segmentStart, middle);
        initialize(arr, 2 * currentNode + 2, middle + 1, segmentEnd);
        segmentTree[currentNode] = getValue(2 * currentNode + 1) + getValue(2 * currentNode + 2);
    }
}

void RangeManager::addValue(int index, int value) {
    modify(0, 0, arraySize - 1, index, value);
}

void RangeManager::modify(int currentNode, int segmentStart, int segmentEnd, int index, int value) {
    if (segmentStart == segmentEnd) {
        segmentTree[currentNode] = getValue(currentNode) + value;
    } else {
        int middle = (segmentStart + segmentEnd) / 2;
        if (index <= middle) {
            modify(2 * currentNode + 1, segmentStart, middle, index, value);
        } else {
            modify(2 * currentNode + 2, middle + 1, segmentEnd, index, value);
        }
        segmentTree[currentNode] = getValue(2 * currentNode + 1) + getValue(2 * currentNode + 2);
    }
}

long long RangeManager::querySum(int left, int right) {
    return calculateSum(0, 0, arraySize - 1, left, right - 1);
}

long long RangeManager::calculateSum(int currentNode, int segmentStart, int segmentEnd, int queryStart, int queryEnd) {
    if (queryEnd < segmentStart || segmentEnd < queryStart) {
        return 0;
    }
    if (queryStart <= segmentStart && segmentEnd <= queryEnd) {
        return getValue(currentNode);
    }
    int middle = (segmentStart + segmentEnd) / 2;
    long long leftSum = calculateSum(2 * currentNode + 1, segmentStart, middle, queryStart, queryEnd);
    long long rightSum = calculateSum(2 * currentNode + 2, middle + 1, segmentEnd, queryStart, queryEnd);
    return leftSum + rightSum;
}
