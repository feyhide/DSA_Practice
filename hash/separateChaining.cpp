#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;

class Node{
	public:
		
    int key;
    int value;  
    Node* next;

    Node(int k, int v){
        key = k;
        value = v;
        next = NULL;
    }
};

class hash_table_ll{
	
	public:
		
    Node* table[TABLE_SIZE];

    hash_table_ll(){
        for(int i = 0; i < TABLE_SIZE; i++){
            table[i] = NULL;
        }
    }

    int hash(int key){
        return key % TABLE_SIZE;
    }

    void insert_ht(int key, int value){
        int index = hash(key);
        Node* newNode = new Node(key, value);

        if(table[index] == NULL){
            table[index] = newNode;
            cout << "Inserted " << key << " with value " << value << " at index " << index << endl;
        } 
		else{
            
			Node* current = table[index];
            while(current->next != NULL){
                current = current->next;
            }
            //current->next = newNode;
            current->next = newNode;
            cout << "Inserted " << key << " with value " << value << " at index " << index << " (collision handled)" << endl;
        }
    }

    void search_ht(int key){
        int index = hash(key);
        Node* current = table[index];

        while(current != NULL){
            if(current->key == key){
                cout << endl << key << " found in hash table\n"; 
				return; 
            }
            current = current->next;
        }
        cout << endl << key << " not found in hash table\n";  
    }

    void delete_ht(int key){
        int index = hash(key);
        Node* current = table[index];
        Node* prev = NULL;

        while(current != NULL){
            if(current->key == key){
                if(prev == NULL){
                    table[index] = current->next;
                } 
				else{
                    prev->next = current->next;
                }
                delete current;
                cout << "Deleted key " << key << " from index " << index << endl;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "\nKey " << key << " not found in hash table" << endl;
    }

    void print_table(){
        
		for(int i = 0; i < TABLE_SIZE; i++){
            cout << i << ": ";
            Node* current = table[i];
            while(current != NULL){
                cout << "(" << current->key << ", " << current->value << ") -> ";
                current = current->next;
            }
            cout << "NULL" << endl;
        }
    }
};

int main(){
    hash_table_ll h;
    
    h.insert_ht(20, 100);
    h.insert_ht(34, 200);
    h.insert_ht(45, 300);
    h.insert_ht(70, 400);
    h.insert_ht(56, 500);

    cout << "\nHash Table After Insertion:\n";
    h.print_table();

    h.search_ht(34);
    
    h.delete_ht(34);
    h.delete_ht(70);
    h.delete_ht(100); 

    cout << "\nHash Table After Deletions:\n";
    h.print_table();

    return 0;
}

