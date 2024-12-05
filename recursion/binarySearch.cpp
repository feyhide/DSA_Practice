#include<iostream>

using namespace std;

int binarySearch(int *arr,int start,int end,int key){
	if(start > end){
		return 0;
	}
	int mid = start + (end-start)/2;
	if(arr[mid] == key){
		return 1;
	}
	if(key > arr[mid]){
		return binarySearch(arr,mid+1,end,key);
	}else if(key < arr[mid]){
		return binarySearch(arr,start,mid-1,key);
	}
}

int main(){
	int arr[5] = {1,2,3,4,5};
	int end = 5;
	int start = 0;
	int key = 4;
	
	cout<<binarySearch(arr,0,4,key)<<endl;
	return 0;
}
