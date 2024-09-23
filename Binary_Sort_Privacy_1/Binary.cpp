#include <iostream>
#include <vector>

using namespace std;

void binary_search(const vector<int>& arr, int x);

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    int k;
    cin >> k;
    vector<int> a(k);
    
    for (int i = 0; i < k; ++i) 
    {
        cin >> a[i];
    }

    for (int i = 0; i < k; ++i) 
    {
        binary_search(arr, a[i]);
    }

    return 0;
}

void binary_search(const vector<int>& arr, int x)
{
    int n = arr.size();
    int l = 0, r = n;

    while (l < r)
    {
        int mid = (l + r) / 2;
        if (arr[mid] >= x) 
        {
            r = mid;
        } 
        else 
        {
            l = mid + 1;
        }
    }

    int left = l;

    l = 0, r = n;

    while (l < r)
    {
        int mid = (l + r) / 2;
        if (arr[mid] > x) 
        {
            r = mid;
        } 
        else 
        {
            l = mid + 1;
        }
    }

    int right = l;

    if (left < n && arr[left] == x)
    {
        cout << 1 << " " << left << " " << right << endl;
    } 
    else 
    {
        cout << 0 << " " << left << " " << right << endl;
    }
}
