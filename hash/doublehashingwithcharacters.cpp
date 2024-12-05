#include <iostream>
using namespace std;

class Hashing {
public:
    char* table;  // Array to hold characters
    int size;
    
    Hashing(int s) {
        size = s;
        table = new char[size];
        for (int i = 0; i < size; i++) {
            table[i] = '\0'; // Initialize the table with null characters (indicating empty spots)
        }
    }

    // Double Hashing Insert
    void doubleInsert(char key) {
        int index = key % size;
        int i = 0;
        
        // Secondary hash function: 1 + (key % (size - 1))
        int step = 1 + (key % (size - 1));
        
        while (table[(index + i * step) % size] != '\0') {
            i++;
        }
        
        table[(index + i * step) % size] = key;
    }

    // Display the hash table
    void displayTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] != '\0')
                cout << "Index " << i << ": " << table[i] << endl;
            else
                cout << "Index " << i << ": Empty" << endl;
        }
    }

    // Double Hashing Search
    bool doubleSearch(char key) {
        int index = key % size;
        int i = 0;
        int step = 1 + (key % (size - 1));

        // Double hashing for search
        while (table[(index + i * step) % size] != '\0') {
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
    cout << "Double Hashing for Characters:" << endl;
    h.doubleInsert('A');
    h.doubleInsert('B');
    h.doubleInsert('C');
    h.doubleInsert('D');
    h.displayTable();
    cout << endl;

    // Searching for characters
    cout << "Searching for 'A': " << (h.doubleSearch('A') ? "Found" : "Not Found") << endl;
    cout << "Searching for 'E': " << (h.doubleSearch('E') ? "Found" : "Not Found") << endl;

    return 0;
}

