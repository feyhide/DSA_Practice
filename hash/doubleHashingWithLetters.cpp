#include <iostream>
#include <string>
using namespace std;

class Hashing {
public:
    string* table;  // Array to hold words (strings)
    int size;
    
    Hashing(int s) {
        size = s;
        table = new string[size];
        for (int i = 0; i < size; i++) {
            table[i] = ""; // Initialize the table with empty strings (indicating empty spots)
        }
    }

    // Double Hashing Insert for words (strings)
    void doubleInsert(const string& key) {
        int index = hashFunction(key);
        int i = 0;
        
        // Secondary hash function: 1 + (key % (size - 1))
        int step = 1 + (index % (size - 1));
        
        while (table[(index + i * step) % size] != "") {
            i++;
        }
        
        table[(index + i * step) % size] = key;
    }

    // Hash function to convert string to integer (sum of ASCII values of characters)
    int hashFunction(const string& key) {
        int hashValue = 0;
        for (char ch : key) {
            hashValue += ch;  // Summing ASCII values of characters
        }
        return hashValue % size;
    }

    // Display the hash table
    void displayTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] != "")
                cout << "Index " << i << ": " << table[i] << endl;
            else
                cout << "Index " << i << ": Empty" << endl;
        }
    }

    // Double Hashing Search for words (strings)
    bool doubleSearch(const string& key) {
        int index = hashFunction(key);
        int i = 0;
        int step = 1 + (index % (size - 1));

        // Double hashing for search
        while (table[(index + i * step) % size] != "") {
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
    cout << "Double Hashing for Words (Strings):" << endl;
    h.doubleInsert("Apple");
    h.doubleInsert("Banana");
    h.doubleInsert("Orange");
    h.doubleInsert("Grapes");
    h.displayTable();
    cout << endl;

    // Searching for words
    cout << "Searching for 'Apple': " << (h.doubleSearch("Apple") ? "Found" : "Not Found") << endl;
    cout << "Searching for 'Mango': " << (h.doubleSearch("Mango") ? "Found" : "Not Found") << endl;
	
    return 0;
}

