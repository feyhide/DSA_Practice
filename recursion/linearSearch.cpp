#include<iostream>

using namespace std;

int linearSearch(int *arr,int size,int key){
	if(size == 0){
		return 0;
	}
	if(arr[0] == key){
		return 1;
	}
	linearSearch(arr+1,size-1,key);
}

int main(){
	int arr[5] = {1,2,3,4,5};
	int size = 5;
	int key = 8;
	
	cout<<linearSearch(arr,size,key)<<endl;
	return 0;
}
