#include<iostream>

using namespace std;

int checkIsSorted(int *arr,int size){
	if(size == 0 || size == 1){
		return 1;
	}
	if(arr[0]>arr[1]){
		return 0;
	}	
	bool ans = checkIsSorted(arr+1,size-1);
}

int main(){
	int arr[5] = {1,7,3,4,5};
	int size = 5;
	
	cout<<checkIsSorted(arr,size);
	return 0;
}
