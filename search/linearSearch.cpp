#include<iostream>
using namespace std;

bool search(int arr[],int size,int key){
	for(int i = 0; i<size; i++){
		if(arr[i]==key){
			return true;
		}
	}
	return false;
}

int main(){
	int arr[10] ={1,2,5,4,3,8,7,6,10,9};
	int key = 5;
	
	cout<<search(arr,10,key);
	return 0;
}
