#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool isHeap(const vector<int>& arr, int n);

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n;
    input >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; ++i) 
    {
        input >> arr[i];
    }

    if (isHeap(arr, n)) {
        output << "Yes" << endl;
    } else {
        output << "No" << endl;
    }

    input.close();
    output.close();

    return 0;
}

bool isHeap(const vector<int>& arr, int n) 
{
    for (int i = 0; i < n / 2; ++i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[i] > arr[left]) 
        {
            return false;
        }

        if (right < n && arr[i] > arr[right]) 
        {
            return false;
        }
    }
    return true;
}
