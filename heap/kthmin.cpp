#include<iostream>
using namespace std;

#include<iostream>
using namespace std;

class heap {
    public:
        int arr[100];
        int size;

        heap() {
            size = 0;
            arr[0] = -1; 
		}

        void insert(int val) {
            size++;
            int index = size;
            arr[index] = val;

            while (index > 1) {
                int parent = index / 2;
                if (arr[parent] < arr[index]) {
                    swap(arr[parent], arr[index]);
                    index = parent;
                } else {
                    return;
                }
            }
        }

        void heapifyDown(int i) {
            int leftIndex = 2 * i;
            int rightIndex = 2 * i + 1;
            int largest = i;

            if (leftIndex <= size && arr[leftIndex] > arr[largest]) {
                largest = leftIndex;
            }
            if (rightIndex <= size && arr[rightIndex] > arr[largest]) {
                largest = rightIndex;
            }

            if (largest != i) {
                swap(arr[i], arr[largest]);
                heapifyDown(largest);  
            }
        }

        void _delete() {
            if (size == 0) {
                cout << "Heap is empty!" << endl;
                return;
            }

            arr[1] = arr[size];
            size--;

            heapifyDown(1);  
        }

        void print() {
            for (int i = 1; i <= size; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
};

int main() {
    heap h1;
    
    int arr[6] = {7,10,4,3,20,15};
    int k = 2;
    for(int i = 0; i <= k-1; i++){
    	h1.insert(arr[i]);
	}
	
	for(int i = k; i < 6; i++){
		if(arr[i] < h1.arr[1]){
			h1._delete();
			h1.insert(arr[i]);
		}
	}
	
	cout<<"kth min"<<h1.arr[1];
	
    return 0;
} 
