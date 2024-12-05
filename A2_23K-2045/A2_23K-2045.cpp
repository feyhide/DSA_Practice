#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;
using namespace std::chrono;

int intValidation(string type) {
	int num;
    while (true) {
        cout << "Enter " << type << " : ";
        if (cin >> num && num > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return num; 
        } else {
            cout << "Invalid " << type << ". Please enter a correct value"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
}

string strValidation(string type) {
	string str;
    while (true) {
        cout << "Enter " << type << ": ";
        getline(cin, str); 
        if (!str.empty()) {  
            return str;
        } else {
            cout << "Invalid " << type << ". Please enter a non-empty string." << endl;
        }
    }
}

struct Record {
    int id;
    string name;
    int age;

    Record(int id, string name, int age) : id(id), name(name), age(age) {}
};

class BST_Node {
public:
    Record data;
    BST_Node* left;
    BST_Node* right;

    BST_Node(Record data) : data(data), left(NULL), right(NULL) {}
};

class BST {
private:
    BST_Node* root;
    int autoIncrementID; 
    int noOfRecords;

    BST_Node* insertNode(BST_Node* node, Record data) {
        if (node == NULL) {
        	noOfRecords++;
            return new BST_Node(data);
        }
        if (data.id < node->data.id) {
            node->left = insertNode(node->left, data);
        } else if (data.id > node->data.id) {
            node->right = insertNode(node->right, data);
        }
        return node;
    }

    void searchNode(BST_Node* node, int id) {
        if (node == NULL){
        	cout << "No record found in BST with id = " << id << endl;
        	return;
		}
        if (node->data.id == id){
        	cout << "Record Found in BST" << endl;
            cout << "ID: " << node->data.id << ", Name: " << node->data.name << ", Age: " << node->data.age << endl;
        	return;
		}
        if (id < node->data.id){
        	searchNode(node->left, id);
		}else if(id > node->data.id){
			searchNode(node->right, id);
		}
        
    }
    
    void updateNode(BST_Node* node, int id, string u_name, int u_age) {
        if (node == NULL){
        	cout << "No record found in BST with id = " << id << endl;
        	return;
		}
        if (node->data.id == id){
        	cout << "Record Updated in BST" << endl;
            cout << "From = " ;
			cout << "ID: " << node->data.id << ", Name: " << node->data.name << ", Age: " << node->data.age << endl;
        	node->data.name = u_name;
        	node->data.age = u_age;
        	cout << "To = " ;
			cout << "ID: " << node->data.id << ", Name: " << node->data.name << ", Age: " << node->data.age << endl;
			return;
		}
        if (id < node->data.id){
        	updateNode(node->left, id, u_name, u_age);
		}else if(id > node->data.id){
        	updateNode(node->right, id, u_name, u_age);
		}
    }

    BST_Node* findMin(BST_Node* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    BST_Node* deleteNode(BST_Node* node, int id) {
        if (node == NULL){
        	cout << "No record found in BST with id = " << id << endl;
        	return NULL;
		}
		
        if (id < node->data.id) {
            node->left = deleteNode(node->left, id);
        } else if (id > node->data.id) {
            node->right = deleteNode(node->right, id);
        } else {
            if (node->left == NULL) {
                BST_Node* temp = node->right;
            	cout << "Record deleted in BST with id = " << id << endl;
        		noOfRecords--;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                BST_Node* temp = node->left;
        		noOfRecords--;
                delete node;
                return temp;
            }
            BST_Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data.id);
        }
        return node;
    }

    void printData(BST_Node* node, int limit) {
    	if(noOfRecords == 0){
    		cout << "No Records Added in BST" << endl;
			return;
		}
        if (node != NULL) {
        	if(limit == 0){
        		return;
			}
            printData(node->left, limit);
            cout << "ID: " << node->data.id << ", Name: " << node->data.name << ", Age: " << node->data.age << endl;
           	limit--;
		    printData(node->right, limit);
        }
    }

public:
    BST() : root(NULL), noOfRecords(0) {}
    
	void dummyInsertOne(int id,string name, int age) {
        Record newRecord(id, name, age);
        root = insertNode(root, newRecord);
    }
    
    void insertOne(int id,string name, int age) {
    	cout << endl;
        Record newRecord(id, name, age);
        root = insertNode(root, newRecord);
        cout << endl;
    }

    void findById(int id) {
    	cout << endl;
        searchNode(root, id);
    	cout << endl;
	}

    void findByIdAndRemove(int id) {
    	cout << endl;
        root = deleteNode(root, id);
		cout << endl;
    }
    
    void findByIdAndUpdate(int id, string name, int age) {
    	cout << endl;
        updateNode(root, id, name, age);
        cout << endl;
    }

    void find(int limit = -1) {
    	if(limit == -1){
    		limit = noOfRecords;
		}
    	cout << endl;
    	cout << "Printing all records from BST" << endl;
        printData(root,limit);
        cout << "Total Records = " << noOfRecords << endl;
        cout << endl;
    }
};

class AVL_Node {
public:
    Record data;  
    AVL_Node* left;
    AVL_Node* right;
    int height;

    AVL_Node(Record data) : data(data), left(NULL), right(NULL), height(1) {}
};

class AVL {
private:
    AVL_Node* root;
	int noOfRecords;
	
    int getHeight(AVL_Node* node) {
        return node == NULL ? 0 : node->height;
    }

    int getBalanceFactor(AVL_Node* node) {
        if (!node){
        	return 0;
		}
        return getHeight(node->left) - getHeight(node->right);
    }

    AVL_Node* leftRotate(AVL_Node* y) {
        AVL_Node* x = y->right;
        AVL_Node* T2 = x->left;

        x->left = y;
        y->right = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVL_Node* rightRotate(AVL_Node* x) {
        AVL_Node* y = x->left;
        AVL_Node* T2 = y->right;

        y->right = x;
        x->left = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVL_Node* insertNode(AVL_Node* node, Record data) {
        if (node == NULL) {
        	noOfRecords++;
            return new AVL_Node(data);
        }

        if (data.id < node->data.id) {
            node->left = insertNode(node->left, data);
        } else if (data.id > node->data.id) {
            node->right = insertNode(node->right, data);
        } else {
            return node;  
        }
        
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1 && data.id < node->left->data.id) {
            return rightRotate(node);
        }
        if (balanceFactor < -1 && data.id > node->right->data.id) {
            return leftRotate(node);
        }
        if (balanceFactor > 1 && data.id > node->left->data.id) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balanceFactor < -1 && data.id < node->right->data.id) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;  
    }

    void searchNode(AVL_Node* node, int id){
        if(node == NULL){
        	cout << "No record found in AVL with id = " << id << endl;
        	return;
		}
		if (node->data.id == id){
        	cout << "Record Found in AVL" << endl;
            cout << "ID: " << node->data.id << ", Name: " << node->data.name << ", Age: " << node->data.age << endl;
        	return;
		}
        if(id < node->data.id){
        	searchNode(node->left, id);
		}else if(id > node->data.id){
			searchNode(node->right, id);
		}
    }
    
    void updateNode(AVL_Node* node, int id, string u_name, int u_age){
        if(node == NULL){
        	cout << "No Record found in AVL with id = " << id << endl;
        	return;
		}
		if(node->data.id == id){
			cout << "Record Updated in AVL" << endl;
            cout << "From = " ;
			cout << "ID: " << node->data.id << ", Name: " << node->data.name << ", Age: " << node->data.age << endl;
        	node->data.name = u_name;
			node->data.age = u_age;
			cout << "To = " ;
			cout << "ID: " << node->data.id << ", Name: " << node->data.name << ", Age: " << node->data.age << endl;
			return;
		}
        if(id < node->data.id){
        	updateNode(node->left, id, u_name, u_age);
		}else{
			updateNode(node->right, id, u_name, u_age);
		}
    }
    
	AVL_Node* findMin(AVL_Node* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }
    
	AVL_Node* deleteNode(AVL_Node* node, int id) {
		if (node == NULL){
			cout << "No record found in AVL with id = " << id << endl;
        	return node;
		}

        if(id < node->data.id){
            node->left = deleteNode(node->left, id);
        }else if(id > node->data.id){
            node->right = deleteNode(node->right, id);
        }else{
            if(node->left == NULL || node->right == NULL){
                AVL_Node* temp = node->left ? node->left : node->right;

                if(temp == NULL){
                    temp = node;
                    node = NULL;
                }else{
                    *node = *temp;
                }
                cout << "Record deleted in AVL with id = " << id << endl;
                noOfRecords--;
                delete temp;
            } else {
                AVL_Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data.id);
            }
        }

        if (node == NULL){
        	return node;
		}

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void printData(AVL_Node* node, int limit){
        if(noOfRecords == 0){
    		cout << "No Records Added in AVL" << endl;
			return;
		}
		if (node != NULL) {
			if(limit == 0){
        		return;
			}
            printData(node->left, limit);
            cout << "ID: " << node->data.id << ", Name: " << node->data.name << ", Age: " << node->data.age << endl;
            limit--;
			printData(node->right, limit);
        }
    }

public:
    AVL() : root(NULL), noOfRecords(0) {}

    void insertOne(int id,string name, int age) {
    	cout << endl;
    	Record newRecord(id, name, age);
        root = insertNode(root, newRecord);
        cout << endl;
    }
    
    void dummyInsertOne(int id,string name, int age) {
    	Record newRecord(id, name, age);
        root = insertNode(root, newRecord);
    }
    
    void findById(int id) {
		cout << endl;
        searchNode(root, id);
    	cout << endl;
	}

    void findByIdAndRemove(int id) {
    	cout << endl;
        root = deleteNode(root, id);
        cout << endl;
    }
    
    void findByIdAndUpdate(int id, string name, int age){
    	cout << endl;
        updateNode(root, id, name, age);
        cout << endl;
	}

    void find(int limit = -1) {
    	if(limit == -1){
    		limit = noOfRecords;
		}
        cout << endl;
    	cout << "Printing all records from AVL" << endl;
        printData(root,limit);
        cout << "Total Records = " << noOfRecords << endl;
        cout << endl;
    }
};


class BT_Node {
public:
    vector<Record*> data;        
    vector<BT_Node*> childNodes;  
    bool isLeafNode;              
    int maxDataCount;              

    BT_Node(int maxDataCount, bool isLeafNode) {
        this->maxDataCount = maxDataCount;
        this->isLeafNode = isLeafNode;
    }

    void traverseTree(int limit) {
        int i = 0;
        while (i < data.size()) {
            if(limit == 0){
            	return;
			}
			if (!isLeafNode) {
                childNodes[i]->traverseTree(limit);
            }
            cout << "ID: " << data[i]->id << ", Name: " << data[i]->name << ", Age: " << data[i]->age << endl;
            limit--;
			i++;
        }
        if (!isLeafNode) {
            childNodes[i]->traverseTree(limit);
        }
    }

    BT_Node* find(int key) {
        int i = 0;
        while (i < data.size() && key > data[i]->id) {
            i++;
        }

        if (i < data.size() && data[i]->id == key) {
        	cout << "ID: " << data[i]->id << ", Name: " << data[i]->name << ", Age: " << data[i]->age << endl;
            return this;
        }

        return isLeafNode ? NULL : childNodes[i]->find(key);
    }

    void insertData(Record record) {
        int i = data.size() - 1;

        if (isLeafNode) {
            data.push_back(new Record(0, "", 0)); 
            while (i >= 0 && data[i]->id > record.id) {
                data[i + 1] = data[i];
                i--;
            }
            data[i + 1] = new Record(record.id, record.name, record.age);  
        } else {
            while (i >= 0 && data[i]->id > record.id) {
                i--;
            }

            if (childNodes[i + 1]->data.size() == maxDataCount) {
                splitNode(i + 1, childNodes[i + 1]);
                if (data[i + 1]->id < record.id) {
                    i++;
                }
            }

            childNodes[i + 1]->insertData(record);
        }
    }

    void splitNode(int i, BT_Node* node) {
        int mid = maxDataCount / 2;
        BT_Node* newNode = new BT_Node(maxDataCount, node->isLeafNode);

        newNode->data.assign(node->data.begin() + mid + 1, node->data.end());

        if (!node->isLeafNode) {
            newNode->childNodes.assign(node->childNodes.begin() + mid + 1, node->childNodes.end());
        }

        node->data.resize(mid);
        if (!node->isLeafNode) {
            node->childNodes.resize(mid + 1);
        }

        childNodes.insert(childNodes.begin() + i + 1, newNode);
        data.insert(data.begin() + i, node->data[mid]);
    }

    bool deleteData(int key) {
        int i = 0;
        while (i < data.size() && data[i]->id < key) {
            i++;
        }

        if (i < data.size() && data[i]->id == key) {
            if (isLeafNode) {
                data.erase(data.begin() + i);
                return true;
            } else {
                BT_Node* pred = childNodes[i];
                if (pred->data.size() > 1) {
                    Record* predData = pred->data.back();
                    data[i] = predData;
                    return pred->deleteData(predData->id);
                } else {
                    return false;
                }
            }
        }

        if (!isLeafNode) {
            return childNodes[i]->deleteData(key);
        }

        return false;
    }

    void updateData(int key, string newName, int newAge) {
        int i = 0;
        while (i < data.size() && data[i]->id < key) {
            i++;
        }

        if (i < data.size() && data[i]->id == key) {
        	cout << "Record Updated in BT" << endl;
            cout << "From = " ;
			cout << "ID: " << data[i]->id << ", Name: " << data[i]->name << ", Age: " << data[i]->age << endl;
            data[i]->name = newName;
            data[i]->age = newAge;
            cout << "To = " ;
			cout << "ID: " << data[i]->id << ", Name: " << data[i]->name << ", Age: " << data[i]->age << endl;
        } else if (!isLeafNode) {
            childNodes[i]->updateData(key, newName, newAge);
        }
    }
};

class BTree {
private:
    BT_Node* rootNode;
    int maxDegree;
	int noOfRecords;
	
    void traverse(int limit) {
    	if(noOfRecords == 0){
    		cout << "No Records Added in BT" << endl;
			return;
		}
        if (rootNode) {
        	if(limit == 0){
        		return;
			}
            rootNode->traverseTree(limit);
        }
        cout << endl;
    }

    void search(int id) {
        rootNode ? rootNode->find(id) : NULL;
        if(rootNode){
        	cout << "Record Found in BT" << endl;
		}else{
			cout << "No record found in BT with id = " << id << endl;
		}
    }

    void insert(Record record) {
        if (!rootNode) {
            rootNode = new BT_Node(maxDegree, true);
            rootNode->data.push_back(new Record(record.id, record.name, record.age));
        } else {
            if (rootNode->data.size() == maxDegree) {
                BT_Node* newRoot = new BT_Node(maxDegree, false);
                newRoot->childNodes.push_back(rootNode);
                newRoot->splitNode(0, rootNode);
                rootNode = newRoot;
            }
            rootNode->insertData(record);
        }
        noOfRecords++;
    }

    bool deleteRecord(int key) {
        if (rootNode) {
        	noOfRecords--;
            return rootNode->deleteData(key);
		}
        return false;
    }

    void updateRecord(int key, string newName, int newAge) {
        if (rootNode) {
            rootNode->updateData(key, newName, newAge);
        }
    }

public:
    BTree(int degree) : rootNode(NULL), noOfRecords(0), maxDegree(degree-1) {}
	
	void insertOne(int id, string name, int age) {
        cout << endl;
    	Record newRecord(id, name, age);
		insert(newRecord);
        cout << endl;
    }
    
	void dummyInsertOne(int id, string name, int age) {
    	Record newRecord(id, name, age);
		insert(newRecord);
    }
    
    void find(int limit = -1) {
    	if(limit == -1){
    		limit = noOfRecords;
		}
    	cout << endl;
    	cout << "Printing all records from BT" << endl;
        traverse(limit);
        cout << "Total Records = " << noOfRecords << endl;
        cout << endl;
    }

    void findById(int id) {
    	cout << endl;
        search(id);
    	cout << endl;
	}

    bool findByIdAndRemove(int id) {
        cout << endl;
        bool res = deleteRecord(id);
        if(res){
        	cout << "Record deleted in BT with id = " << id << endl;
		}else{
			cout << "No record found in BT with id = " << id << endl;
		}
		cout << endl;
    }

    void findByIdAndUpdate(int id, string name, int age) {
    	cout << endl;
        updateRecord(id, name, age);
    	cout << endl;
	}
};

bool loadDataFromFile(const string& filename, BST& bst, AVL& avl, BTree& btree) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return false;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        int id, age;
        string name;

        ss >> id >> name >> age; 

        bst.dummyInsertOne(id, name, age);
        avl.dummyInsertOne(id, name, age);
        btree.dummyInsertOne(id, name, age);
    }
	cout << "dummy data inserted" << endl;
    file.close();
    return true;
}

int main() {
    BST bst;
    AVL avl;
    BTree btree(9);
    
    int mainChoice;
    cout << "you want to performance test this code (enter 1) or try the complete code (enter 2)" << endl;
    mainChoice = intValidation("Choice");
    
    if(mainChoice == 1){
    	bool res = loadDataFromFile("dummyData.txt", bst, avl, btree);
    	if(!res){
    		return 0;
		}
		while(1) {
	        int choice;
	        cout << "Select any of the database operations" << endl;
	        cout << "1. Find operation in all trees" << endl;
	        cout << "2. Insert operation in all trees" << endl;
	        cout << "3. Update operation in all trees" << endl;
	        cout << "4. Remove operation in all trees" << endl;
	        cout << "5. Find by ID operation in all trees" << endl;
	        choice = intValidation("Choice");
	
	        switch(choice) {
	            case 1: {
	                auto start = high_resolution_clock::now();
	                bst.find();
	                auto stop = high_resolution_clock::now();
	                auto duration = duration_cast<microseconds>(stop - start);
	                cout << "BST find operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                avl.find();
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "AVL find operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                btree.find();
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "B-tree find operation took: " << duration.count() << " microseconds." << endl;
	
	                break;
	            }
	            case 2: {
	                int i_id;
	                string i_name;
	                int i_age;
	
	                i_id = intValidation("Id");
	                i_name = strValidation("Name");
	                i_age = intValidation("Age");
	
	                auto start = high_resolution_clock::now();
	                bst.insertOne(i_id, i_name, i_age);
	                auto stop = high_resolution_clock::now();
	                auto duration = duration_cast<microseconds>(stop - start);
	                cout << "BST insert operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                avl.insertOne(i_id, i_name, i_age);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "AVL insert operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                btree.insertOne(i_id, i_name, i_age);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "B-tree insert operation took: " << duration.count() << " microseconds." << endl;
	
	                break;
	            }
	            case 3: {
	                string u_name;
	                int u_age;
	                int s_id;
	
	                s_id = intValidation("Id");
	                u_name = strValidation("Updated Name");
	                u_age = intValidation("Updated Age");
	
	                auto start = high_resolution_clock::now();
	                bst.findByIdAndUpdate(s_id, u_name, u_age);
	                auto stop = high_resolution_clock::now();
	                auto duration = duration_cast<microseconds>(stop - start);
	                cout << "BST update operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                avl.findByIdAndUpdate(s_id, u_name, u_age);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "AVL update operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                btree.findByIdAndUpdate(s_id, u_name, u_age);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "B-tree update operation took: " << duration.count() << " microseconds." << endl;
	
	                break;
	            }
	            case 4: {
	                int s_id;
	
	                s_id = intValidation("Id");
	
	                auto start = high_resolution_clock::now();
	                bst.findByIdAndRemove(s_id);
	                auto stop = high_resolution_clock::now();
	                auto duration = duration_cast<microseconds>(stop - start);
	                cout << "BST remove operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                avl.findByIdAndRemove(s_id);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "AVL remove operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                btree.findByIdAndRemove(s_id);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "B-tree remove operation took: " << duration.count() << " microseconds." << endl;
	
	                break;
	            }
	            case 5: {
	                int s_id;
	
	                s_id = intValidation("Id");
	
	                auto start = high_resolution_clock::now();
	                bst.findById(s_id);
	                auto stop = high_resolution_clock::now();
	                auto duration = duration_cast<microseconds>(stop - start);
	                cout << "BST find by Id operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                avl.findById(s_id);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "AVL find by Id operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                btree.findById(s_id);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "B-tree find by Id operation took: " << duration.count() << " microseconds." << endl;
	
	                break;
	            }
	            default: {
	                break;
	            }
	        }
	    }
	}else if(mainChoice == 2){
		while(1) {
	        int choice;
	        cout << "Select any of the database operations" << endl;
	        cout << "1. Find operation in all trees" << endl;
	        cout << "2. Insert operation in all trees" << endl;
	        cout << "3. Update operation in all trees" << endl;
	        cout << "4. Remove operation in all trees" << endl;
	        cout << "5. Find by ID operation in all trees" << endl;
	        choice = intValidation("Choice");
	
	        switch(choice) {
	            case 1: {
	                auto start = high_resolution_clock::now();
	                bst.find();
	                auto stop = high_resolution_clock::now();
	                auto duration = duration_cast<microseconds>(stop - start);
	                cout << "BST find operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                avl.find();
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "AVL find operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                btree.find();
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "B-tree find operation took: " << duration.count() << " microseconds." << endl;
	
	                break;
	            }
	            case 2: {
	                int i_id;
	                string i_name;
	                int i_age;
	
	                i_id = intValidation("Id");
	                i_name = strValidation("Name");
	                i_age = intValidation("Age");
	
	                auto start = high_resolution_clock::now();
	                bst.insertOne(i_id, i_name, i_age);
	                auto stop = high_resolution_clock::now();
	                auto duration = duration_cast<microseconds>(stop - start);
	                cout << "BST insert operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                avl.insertOne(i_id, i_name, i_age);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "AVL insert operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                btree.insertOne(i_id, i_name, i_age);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "B-tree insert operation took: " << duration.count() << " microseconds." << endl;
	
	                break;
	            }
	            case 3: {
	                string u_name;
	                int u_age;
	                int s_id;
	
	                s_id = intValidation("Id");
	                u_name = strValidation("Updated Name");
	                u_age = intValidation("Updated Age");
	
	                auto start = high_resolution_clock::now();
	                bst.findByIdAndUpdate(s_id, u_name, u_age);
	                auto stop = high_resolution_clock::now();
	                auto duration = duration_cast<microseconds>(stop - start);
	                cout << "BST update operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                avl.findByIdAndUpdate(s_id, u_name, u_age);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "AVL update operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                btree.findByIdAndUpdate(s_id, u_name, u_age);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "B-tree update operation took: " << duration.count() << " microseconds." << endl;
	
	                break;
	            }
	            case 4: {
	                int s_id;
	
	                s_id = intValidation("Id");
	
	                auto start = high_resolution_clock::now();
	                bst.findByIdAndRemove(s_id);
	                auto stop = high_resolution_clock::now();
	                auto duration = duration_cast<microseconds>(stop - start);
	                cout << "BST remove operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                avl.findByIdAndRemove(s_id);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "AVL remove operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                btree.findByIdAndRemove(s_id);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "B-tree remove operation took: " << duration.count() << " microseconds." << endl;
	
	                break;
	            }
	            case 5: {
	                int s_id;
	
	                s_id = intValidation("Id");
	
	                auto start = high_resolution_clock::now();
	                bst.findById(s_id);
	                auto stop = high_resolution_clock::now();
	                auto duration = duration_cast<microseconds>(stop - start);
	                cout << "BST find by Id operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                avl.findById(s_id);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "AVL find by Id operation took: " << duration.count() << " microseconds." << endl;
	
	                start = high_resolution_clock::now();
	                btree.findById(s_id);
	                stop = high_resolution_clock::now();
	                duration = duration_cast<microseconds>(stop - start);
	                cout << "B-tree find by Id operation took: " << duration.count() << " microseconds." << endl;
	
	                break;
	            }
	            default: {
	                break;
	            }
	        }
	    }
	}else{
		cout << "wrong input" << endl;
	}
    

    return 0;
}


