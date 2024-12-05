#include <iostream>
using namespace std;

class MaxHeap {
public:
    int arr[100];
    int size;

    MaxHeap() {
        size = 0;
        arr[0] = -1; // Dummy value for simpler indexing
    }

    void insert(int val) {
        size++;
        int index = size;
        arr[index] = val;

        while (index > 1) {
            int parent = index / 2;
            if (arr[parent] < arr[index]) { // Parent should be larger for max-heap
                swap(arr[parent], arr[index]);
                index = parent;
            } else {
                return;
            }
        }
    }

    void maxHeapify(int i) {
        int leftIndex = 2 * i;
        int rightIndex = 2 * i + 1;
        int largest = i;

        if (leftIndex <= size && arr[leftIndex] > arr[largest]) {
            largest = leftIndex;
        }
        if (rightIndex <= size && arr[rightIndex] > arr[largest]) {
            largest = rightIndex;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            maxHeapify(largest);  
        }
    }

    void _delete() {
        if (size == 0) {
            cout << "Heap is empty!" << endl;
            return;
        }

        arr[1] = arr[size];
        size--;

        maxHeapify(1);  
    }

    void print() {
        for (int i = 1; i <= size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MaxHeap h1;

    int arr[6] = {7, 10, 4, 3, 20, 15};
    for (int i = 0; i < 6; i++) {
        h1.insert(arr[i]);
    }

    cout << "Max-Heap: ";
    h1.print();

    h1._delete();
    cout << "After deletion: ";
    h1.print();

    return 0;
}

