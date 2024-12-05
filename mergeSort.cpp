#include<iostream>

using namespace std;

void merge(int *arr,int s,int e){
    int mid = s + (e - s) / 2;
	int len1 = mid-s+1;
	int len2 = e-mid;
	int *left = new int[len1];
	int *right = new int[len2];
	
	int mainarrindex = s;
	for(int i = 0; i < len1;i++){
		left[i] = arr[mainarrindex++];
	}
	
	mainarrindex = mid+1;
	for(int i = 0; i < len2;i++){
		right[i] = arr[mainarrindex++];
	}
	
	int index1 =0;
	int index2 =0;
	mainarrindex = s;
	
	while(index1 < len1 && index2 < len2){
		if(left[index1]<right[index2]){
			arr[mainarrindex++] = left[index1++];
		}else{
			arr[mainarrindex++] = right[index2++];
		}
	}
	
	while(index1 < len1){
		arr[mainarrindex++] = left[index1++];
	}
	while(index2 < len2){
		arr[mainarrindex++] = right[index2++];
	}
}

void mergeSort(int *arr,int s,int e){
	if(s>=e){
		return;
	}
	
    int mid = s + (e - s) / 2;
	mergeSort(arr,s,mid);
	mergeSort(arr,mid+1,e); 
	merge(arr,s,e);
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
	mergeSort(arr,0,5-1);
	cout<<endl;
	print(arr,0,5);
	return 0;
}
