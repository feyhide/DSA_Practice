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

        void _delete() {
            if (size == 0) {
                cout << "Heap is empty!" << endl;
                return;
            }

            arr[1] = arr[size];
            size--;

            int i = 1;
            while (i <= size) {
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
                    i = largest;
                } else {
                    return;
                }
            }
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
    h1.insert(54);
    h1.insert(53);
    h1.insert(55);
    h1.insert(52);
    h1.insert(50);
    h1.print();

    h1._delete();
    h1.print();

    return 0;
}

