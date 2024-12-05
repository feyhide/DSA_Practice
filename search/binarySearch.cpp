#include<iostream>
using namespace std;
// montonic function
int binSearch(int arr[],int size,int key){
	int start = 0;
	int end = size - 1;
	int mid = start+(end-start)/2;
	
	while(start<=end){
		if(arr[mid]==key){
			return mid;
		}
		if(key>arr[mid]){
			start = mid+1;
		}
		if(key<arr[mid]){
			end=mid-1;
		}
		 mid = start+(end-start)/2;
	}
	return -1;
}

int main(){
	int arr[5] ={3,5,9,13,27};
	int key = 28;
	
	cout<<binSearch(arr,5,key);
	return 0;
}
