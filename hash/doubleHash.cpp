#include <iostream>
using namespace std;

class Hashing {
public:
    int* table;
    int size;
    
    Hashing(int s) {
        size = s;
        table = new int[size];
        for (int i = 0; i < size; i++) {
            table[i] = -1; // Initialize the table with -1 (indicating empty spots)
        }
    }

    // Double Hashing
    void doubleInsert(int key) {
        int index = key % size;
        int i = 0;
        
        // Secondary hash function: 1 + (key % (size - 1))
        int step = 1 + (key % (size - 1));
        
        while (table[(index + i * step) % size] != -1) {
            i++;
        }
        
        table[(index + i * step) % size] = key;
    }

    // Display the hash table
    void displayTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] != -1)
                cout << "Index " << i << ": " << table[i] << endl;
            else
                cout << "Index " << i << ": Empty" << endl;
        }
    }
    
    
    bool doubleSearch(int key) {
	    int index = key % size;
	    int i = 0;
	    int step = 1 + (key % (size - 1));
	
	    // Double hashing for search
	    while (table[(index + i * step) % size] != -1) {
	        if (table[(index + i * step) % size] == key) {
	            return true; // Key found
	        }
	        i++;
	    }
	    return false; // Key not found
	}
};

int main() {
    int size = 11; // Example size of hash table (prime number)
    Hashing h(size);

    // Double Hashing Insertions
    cout << "Double Hashing:" << endl;
    h.doubleInsert(10);
    h.doubleInsert(20);
    h.doubleInsert(30);
    h.doubleInsert(25);
    h.displayTable();
    cout << endl;
    
    cout<<h.doubleSearch(10)<<endl;
    cout<<h.doubleSearch(0);

    return 0;
}

