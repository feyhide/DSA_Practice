#include<iostream>

using namespace std;

void bubbleSort(int *arr,int n, int i){
	if(n==0 || n == 1){
		return;
	}
	
	if(i == n-1){
		return bubbleSort(arr,n-1,0);
	}
	
	if(arr[i]>arr[i+1]){
		swap(arr[i],arr[i+1]);
	}
	
	return bubbleSort(arr,n,i+1);
}

void print(int *arr,int i,int size){
	if(i==size){
		return;
	}
	cout<<arr[i];
	print(arr,i+1,size);
}
int main(){
	int arr[5] = {1,3,2,4,5};
	print(arr,0,5);
	cout<<endl;
	bubbleSort(arr,5,0);
	cout<<endl;
	print(arr,0,5);
	return 0;
}
