#include <iostream>
#include <string>
using namespace std;

// Define a struct with two fields: word and frequency
struct WordFrequency {
    string word;
    int frequency;
};

// Bubble Sort function
void bubbleSort(WordFrequency arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].frequency > arr[j + 1].frequency || 
                (arr[j].frequency == arr[j + 1].frequency && arr[j].word > arr[j + 1].word)) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort function
void selectionSort(WordFrequency arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].frequency < arr[minIdx].frequency || 
                (arr[j].frequency == arr[minIdx].frequency && arr[j].word < arr[minIdx].word)) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Insertion Sort function
void insertionSort(WordFrequency arr[], int n) {
    for (int i = 1; i < n; i++) {
        WordFrequency key = arr[i];
        int j = i - 1;
        while (j >= 0 && (arr[j].frequency > key.frequency || 
                         (arr[j].frequency == key.frequency && arr[j].word > key.word))) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort helper function
void merge(WordFrequency arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    WordFrequency L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].frequency < R[j].frequency || 
            (L[i].frequency == R[j].frequency && L[i].word < R[j].word)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(WordFrequency arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Quick Sort function
int partition(WordFrequency arr[], int low, int high) {
    WordFrequency pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].frequency < pivot.frequency || 
            (arr[j].frequency == pivot.frequency && arr[j].word < pivot.word)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(WordFrequency arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to display the sorted array
void displayArray(const WordFrequency arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Word: " << arr[i].word << ", Frequency: " << arr[i].frequency << endl;
    }
}

void copyArray(WordFrequency* src, WordFrequency* dest, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];  // Copy each element from src to dest
    }
}

int main() {
    WordFrequency words[] = {
        {"apple", 5},
        {"banana", 3},
        {"orange", 5},
        {"grapes", 2},
        {"pear", 3},
        {"melon", 2}
    };

    int n = sizeof(words) / sizeof(words[0]);

    // Display original array
    cout << "Original Array:" << endl;
    displayArray(words, n);
    cout << endl;

    // Copy the original array for each sorting method
    WordFrequency arrBubble[n], arrSelection[n], arrInsertion[n], arrMerge[n], arrQuick[n];
    copyArray(words,arrBubble,n);
    copyArray(words,arrSelection,n);
    copyArray(words,arrInsertion,n);
    copyArray(words,arrMerge,n);
    copyArray(words,arrQuick,n);

    // Bubble Sort
    cout << "Bubble Sort:" << endl;
    bubbleSort(arrBubble, n);
    displayArray(arrBubble, n);
    cout << endl;

    // Selection Sort
    cout << "Selection Sort:" << endl;
    selectionSort(arrSelection, n);
    displayArray(arrSelection, n);
    cout << endl;

    // Insertion Sort
    cout << "Insertion Sort:" << endl;
    insertionSort(arrInsertion, n);
    displayArray(arrInsertion, n);
    cout << endl;

    // Merge Sort
    cout << "Merge Sort:" << endl;
    mergeSort(arrMerge, 0, n - 1);
    displayArray(arrMerge, n);
    cout << endl;

    // Quick Sort
    cout << "Quick Sort:" << endl;
    quickSort(arrQuick, 0, n - 1);
    displayArray(arrQuick, n);
    cout << endl;

    return 0;
}

