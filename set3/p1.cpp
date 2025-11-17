#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int>& arr, int size, int i) {
    while (true) {
        int left  = 2 * i + 1;
        int right = 2 * i + 2;

        if (left > size)
            break;
        int root = i;
        if (arr[left] > arr[root])
            root = left;
        if (right < size && arr[right] > arr[root])
            root = right;
        if (root == i)
            break;

        swap(arr[i], arr[root]);
        i = root;
    }
}

void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
        
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    buildMaxHeap(arr);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    heapSort(arr);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << ' ';
    }
}
