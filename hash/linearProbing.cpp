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

    // Linear Probing Hashing
    void linearInsert(int key) {
        int index = key % size;
        int i = 0;
        
        // Linear probing for collision resolution
        while (table[(index + i) % size] != -1) {
            i++;
        }
        
        table[(index + i) % size] = key;
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
};

int main() {
    int size = 11; // Example size of hash table (prime number)
    Hashing h(size);

    // Linear Hashing Insertions
    cout << "Linear Probing:" << endl;
    h.linearInsert(10);
    h.linearInsert(20);
    h.linearInsert(30);
    h.linearInsert(25);
    h.displayTable();
    cout << endl;

    return 0;
}

