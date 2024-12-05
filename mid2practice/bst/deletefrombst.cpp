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

int minInBst(node* root){
	if(root == NULL){
		return -1;
	}
	node* temp = root;
	while(temp->left){
		temp = temp->left;
	}
	return temp->data;
}

int maxInBst(node* root){
	if(root == NULL){
		return -1;
	}
	node* temp = root;
	while(temp->right){
		temp = temp->right;
	}
	return temp->data;
}

node* deletefrombst(node* root, int data){
	if(root == NULL){
		return NULL;
	}
	
	if(root->data == data){
		if(root->left == NULL && root->right == NULL){
			delete root;
			return NULL;
		}
		
		if(root->left != NULL && root->right == NULL){
			node* temp = root->left;
			delete root;
			return temp;
		}
		if(root->left == NULL && root->right != NULL){
			node* temp = root->right;
			delete root;
			return temp;
		}
		
		if(root->left && root->right){
			int mini = minInBst(root->right);
			root->data = mini;
			root->right = deletefrombst(root->right,mini);
			return root;
		}
		
	}else if(root->data > data){
		root->left = deletefrombst(root->left,data);
		return root;
	}else if(root->data < data){
		root->right = deletefrombst(root->right,data);
		return root;
	}
}

int main(){
	node* root = NULL;
	
	cout << "enter data to create bst" << endl;
	
	takeInput(root);
	cout<<endl;
	levelOrderTraversal(root);
	cout<<endl;
	cout<<"enter val to delete : ";
	int data;
	cin>>data;
	root = deletefrombst(root,data);
	cout<<endl;
	levelOrderTraversal(root);
	return 0;
}
