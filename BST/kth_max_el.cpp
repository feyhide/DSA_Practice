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

int kthMAX(node* root, int &i,int k){
	if(root == NULL){
		return -1;
	}
	
	int right = kthMAX(root->right,i,k);
	
	if(right != -1){
		return right;
	}
	
	i++;
	if(i==k){
		return root->data;
	}
	
	return kthMAX(root->left,i,k);
}

void revinorder(node* root,int &i, int key){
	if (root == NULL || i >= key) {
        return;
    }
	revinorder(root->right,i,key);
	i++;
	if(i == key){
		cout<<root->data<<" ";
		return;
	}
	revinorder(root->left,i,key);
}

int main(){
	node* root = NULL;
	
	cout << "enter data to create bst" << endl;
	
	takeInput(root);
	cout<<endl;
	levelOrderTraversal(root);
	cout<<endl; 
	int k = 3;
	int i = 0;
	cout<<endl;
	cout << kthMAX(root,i,k) << endl;
	//or
	i = 0;
	revinorder(root,i,k);
	return 0;
}
