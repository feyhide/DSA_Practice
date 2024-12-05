#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Struct to represent a node in the heap
struct HeapNode {
    int distance;     // Squared distance from origin
    int x, y;         // Coordinates of the tower

    HeapNode(int d, int a, int b) : distance(d), x(a), y(b) {}
};

// Max-Heap class
class MaxHeap {
public:
    HeapNode* arr[100]; // Array to store pointers to HeapNode objects
    int size;

    MaxHeap() {
        size = 0;
        arr[0] = nullptr; // Dummy value for simpler indexing
    }

    void insert(HeapNode* val) {
        size++;
        int index = size;
        arr[index] = val;

        // Heapify up
        while (index > 1) {
            int parent = index / 2;
            if (arr[parent]->distance < arr[index]->distance) { // Max-heap property
                swap(arr[parent], arr[index]);
                index = parent;
            } else {
                return;
            }
        }
    }

    void heapifyDown(int i) {
        int leftIndex = 2 * i;
        int rightIndex = 2 * i + 1;
        int largest = i;

        if (leftIndex <= size && arr[leftIndex]->distance > arr[largest]->distance) {
            largest = leftIndex;
        }
        if (rightIndex <= size && arr[rightIndex]->distance > arr[largest]->distance) {
            largest = rightIndex;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapifyDown(largest);
        }
    }

    void _delete() {
        if (size == 0) {
            cout << "Heap is empty!" << endl;
            return;
        }

        arr[1] = arr[size];
        size--;

        heapifyDown(1);
    }

    HeapNode* getMax() {
        if (size == 0) {
            cout << "Heap is empty!" << endl;
            return nullptr;
        }
        return arr[1]; // Return the max element in the heap
    }

    void print() {
        for (int i = 1; i <= size; i++) {
            cout << "(" << arr[i]->x << ", " << arr[i]->y << ") -> " << arr[i]->distance << endl;
        }
    }
};

// Function to calculate squared distance from the origin
int squaredDistance(int x, int y) {
    return x * x + y * y;
}

int main() {
    MaxHeap h1;

    // Tower coordinates
    vector<pair<int, int>> towers = {{1, 3}, {2, -2}, {5, 8}, {0, 1}, {7, 6}};
    int k = 3; // Number of closest towers to find

    // Step 1: Insert the first k towers into the heap
    for (int i = 0; i < k; i++) {
        int dist = squaredDistance(towers[i].first, towers[i].second);
        h1.insert(new HeapNode(dist, towers[i].first, towers[i].second));
    }

    // Step 2: Process the remaining towers
    for (int i = k; i < towers.size(); i++) {
        int dist = squaredDistance(towers[i].first, towers[i].second);
        if (dist < h1.getMax()->distance) { // Replace the max distance if the current one is smaller
            h1._delete();
            h1.insert(new HeapNode(dist, towers[i].first, towers[i].second));
        }
    }

    // Step 3: Output the result
    cout << "The " << k << " closest towers to (0, 0) are:" << endl;
    h1.print();

    return 0;
}

