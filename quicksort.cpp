#include<iostream>

using namespace std;

int partition(int *arr,int s,int e){
	int pivot = arr[s];
	int count = 0;
	for(int i = s+1; i <= e; i++){
		if(arr[i] <= pivot){
			count++;
		}
	}
	int pivotIndex = s+count;
	swap(arr[pivotIndex],arr[s]);
	
	int i = s;
	int j = e;
	
	while(i < pivotIndex && j > pivotIndex){
		while(arr[i] <= pivot){
			i++;
		}
		while(arr[j] > pivot){
			j--;
		}
		if(i < pivotIndex && j > pivotIndex){
			swap(arr[i++],arr[j--]);
		}
	}
	return pivotIndex;
}

void quickSort(int *arr,int s,int e){
	if(s>=e){
		return;
	}
	int p = partition(arr,s,e);
	quickSort(arr,s,p-1);
	quickSort(arr,p+1,e);
}

void print(int *arr, int s,int e){
	if(s > e){
		return;
	}
	cout<<arr[s];
	print(arr,s+1,e);
}

int main(){
	int arr[5] = {1,2,3,5,4};
	print(arr,0,4);
	cout<<endl;
	quickSort(arr,0,4);
	print(arr,0,4);
	return 0;
}
