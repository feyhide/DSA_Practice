#include <iostream>
#include <vector>
using namespace std;

void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

vector<int> mergeTwo(vector<int>& a, vector<int>& b) {
    vector<int> ans = a;

    for (int i : b) {
        ans.push_back(i);
    }

    int n = ans.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(ans, n, i);
    }

    return ans;
}

int main() {
    vector<int> heap1 = {54, 53, 55, 52, 50};
    vector<int> heap2 = {45, 40, 42, 39, 30};

    vector<int> mergedHeap = mergeTwo(heap1, heap2);

    for (int i : mergedHeap) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

