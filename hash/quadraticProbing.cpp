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

    // Quadratic Probing Hashing
    void quadraticInsert(int key) {
        int index = key % size;
        int i = 0;
        
        // Quadratic probing for collision resolution
        while (table[(index + i * i) % size] != -1) {
            i++;
        }
        
        table[(index + i * i) % size] = key;
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
    
    bool quadSearch(int key) {
	    int index = key % size;
	    int i = 0;
	
	    // Linear probing for search
	    while (table[(index + i*i) % size] != -1) {
	        if (table[(index + i*i) % size] == key) {
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
    
    cout << "Quadratic Probing:" << endl;
    h.quadraticInsert(10);
    h.quadraticInsert(20);
    h.quadraticInsert(30);
    h.quadraticInsert(25);
    h.displayTable();
    
    cout<<h.quadSearch(40)<<endl;
    cout<<h.quadSearch(20)<<endl;

    return 0;
}

