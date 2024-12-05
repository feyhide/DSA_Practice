#include <iostream>
using namespace std;

void bubblesort(int arr[], int size) {
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size-i-1; j++){
			if(arr[j]>arr[j+1]){
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}	
	}
}

void print(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[10] = {1, 2, 5, 4, 3, 8, 7, 6, 10, 9};
    print(arr, 10);
    bubblesort(arr, 10);
    print(arr, 10);

    return 0;
}

