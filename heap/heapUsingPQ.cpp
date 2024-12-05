#include<iostream>
#include<queue>

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

void printPQ(priority_queue<int> pq){
	priority_queue<int> temp = pq;
	
	while(!temp.empty()){
		cout<<temp.top()<<" ";
		temp.pop();
	}
	cout<<endl;
}

int main(){
    //max heap hota hai
	priority_queue<int> pq;
	
	pq.push(4);
	pq.push(2);
	pq.push(1);
	pq.push(5);
	pq.push(3);
	
	printPQ(pq);
	return 0;
}
