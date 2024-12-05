#include <iostream>
using namespace std;

void insertionsort(int arr[], int size) {
	for(int i = 1; i < size; i++){
		int temp = arr[i];
		int j = i-1;
		for(; j >= 0; j--){
			if(temp<arr[j]){
				arr[j+1] = arr[j];
			}else{
				break;
			}
		}
		arr[j+1] = temp;
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
    insertionsort(arr, 10);
    print(arr, 10);

    return 0;
}

