#include<iostream>
#include<queue>

using namespace std;

class node{
	public:
		int data;
		node* left;
		node* right;
		
		node(int d){
			this->data = d;
			this->left = NULL;
			this->right = NULL;
		}
};

void levelOrderTraversal(node* root){
	queue<node*> q;
	q.push(root);
	q.push(NULL);
	
	while(!q.empty()){
		node* temp = q.front();
		q.pop();
		
		if(temp == NULL){
			cout<<endl;
			if(!q.empty()){
				q.push(NULL);
			}
		}else{
			cout<< temp->data << " ";
			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}
	}
}

node* insertIntoBst(node* &root,int data){
	if(root == NULL){
		root = new node(data);
		return root;
	}
	
	if(data > root->data){
		root->right = insertIntoBst(root->right,data);
	}else{
		root->left = insertIntoBst(root->left,data);
	}
	return root;
}

void takeInput(node* &root){
	int data;
	cin >> data;
	
	while(data != -1){
		root = insertIntoBst(root,data);
		cin>>data;
	}
}

int searchInBst(node* root,int key){
	if(root == NULL){
		return -1;
	}	
	
	if(key == root->data){
		return 1;
	}
	
	if(key > root->data){
		return searchInBst(root->right,key);
	}else if (key < root->data){
		return searchInBst(root->left,key);
	}
}

int main(){
	node* root = NULL;
	
	cout << "enter data to create bst" << endl;
	
	takeInput(root);
	cout<<endl;
	levelOrderTraversal(root);
	cout<<endl;
	cout << "enter element to search : ";
	int key;
	cin >> key;
	cout << searchInBst(root,key);
	return 0;
}
