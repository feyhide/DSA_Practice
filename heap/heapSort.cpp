#include<iostream>

using namespace std;


void maxHeapify(int arr[],int n,int i){
	int largest = i;
	int left = 2*i;
	int right = 2*i+1;
	
	if(left <= n && arr[left] > arr[largest]){
		largest = left;
	}
	
	if(right <= n && arr[right] > arr[largest]){
		largest = right;
	}
	
	if(largest != i){
		swap(arr[largest],arr[i]);
		i = largest;
		maxHeapify(arr,n,i);
	}
}

void heapSort(int arr[],int n){
	int size = n;
	
	while(size > 1){
		swap(arr[size],arr[1]);
		size--;
		maxHeapify(arr,size,1);
	}
}

int main(){
	int arr[6] = {-1,54,53,51,52,50};
	int n = 5;
	
	for(int i = n/2; i > 0; i--){
		maxHeapify(arr,n,i);
	}
	
	for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    heapSort(arr,n);
    
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
	
	return 0;
}
