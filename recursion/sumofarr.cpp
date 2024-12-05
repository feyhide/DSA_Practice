#include<iostream>

using namespace std;

int sum(int *arr,int size){
	if(size == 0){
		return *arr;
	}
	return *arr+sum(arr+1,size-1);
}

int _sum(int *arr,int size){
	if(size == 0){
		return *arr;
	}
	int smallerproblem = _sum(arr+1,size-1);
	int biggerproblem = *arr + smallerproblem;
	return biggerproblem;
}

int main(){
	int arr[5] = {1,2,3,4,5};
	int size = 5;
	
	cout<<sum(arr,size)<<endl;
	cout<<_sum(arr,size);
	return 0;
}
