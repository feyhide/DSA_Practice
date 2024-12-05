#include <iostream>
using namespace std;

// Function to perform interpolation search
int interpolationSearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // Estimate the position of the target
        int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);

        // Check if the target is found
        if (arr[pos] == target) {
            return pos; // Target found at index pos
        }

        // If the target is larger, ignore the left half
        if (arr[pos] < target) {
            low = pos + 1;
        }
        // If the target is smaller, ignore the right half
        else {
            high = pos - 1;
        }
    }

    return -1; // Target not found
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 70;

    cout << "Array: ";
    printArray(arr, size);

    int result = interpolationSearch(arr, size, target);

    if (result != -1) {
        cout << "Element found at index: " << result << endl;
    } else {
        cout << "Element not found!" << endl;
    }

    return 0;
}

