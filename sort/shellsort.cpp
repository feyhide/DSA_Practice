#include <iostream>
using namespace std;

void shellSort(int arr[], int size) {
    int gaps[] = {1,2,4,8};
    int gapCount = sizeof(gaps) / sizeof(gaps[0]);
	for (int i = 0;i < gapCount; i++) {
		int currentGap = gaps[i];
        for (int j = currentGap; j < size; j++) {
            int temp = arr[j];
            int k = j;

            while (k >= currentGap && arr[k - currentGap] > temp) {
                arr[k] = arr[k - currentGap];
                k -= currentGap;
            }
            arr[k] = temp; 
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[10] = {10, 7, 8, 9, 1, 5, 3, 6, 2, 4};
    cout << "Original array: ";
    printArray(arr, 10);

    shellSort(arr, 10);

    cout << "Sorted array: ";
    printArray(arr, 10);

    return 0;
}

