#include<iostream>
using namespace std;

void maxHeapify(int arr[],int n, int i){
	int largest = i;
	int left = i*2;
	int right = i*2 + 1;
	
	if(left < n && arr[left] > arr[largest]){
		largest = left;
	}else if(right < n && arr[right] > arr[largest]){
		largest = right;
	}
	
	if(largest != i){
		swap(arr[largest],arr[i]);
		i = largest;
		maxHeapify(arr,n,i);
	}
}

void minHeapify(int arr[],int n, int i){
	int smallest = i;
	int left = i*2;
	int right = i*2 + 1;
	
	if(left < n && arr[left] < arr[smallest]){
		smallest = left;
	}else if(right < n && arr[right] < arr[smallest]){
		smallest = right;
	}
	
	if(smallest != i){
		swap(arr[smallest],arr[i]);
		i = smallest;
		minHeapify(arr,n,i);
	}
}

int main() {
	
	int arr[6] = {-1,54,53,55,52,50};
	int n = 5;
	
	for(int i = n/2; i > 0; i--){
		maxHeapify(arr,n,i);
	}
	
	for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
	
	
	for(int i = n/2; i > 0; i--){
		minHeapify(arr,n,i);
	}
	
	for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
	
	
    return 0;
}

