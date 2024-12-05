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

int kthMIN(node* root, int &i,int k){
	if(root == NULL){
		return -1;
	}
	
	int left = kthMIN(root->left,i,k);
	
	if(left != -1){
		return left;
	}
	
	i++;
	if(i==k){
		return root->data;
	}
	
	return kthMIN(root->right,i,k);
}

void inorder(node* root,int &i, int key){
	if (root == NULL || i >= key) {
        return;
    }
	inorder(root->left,i,key);
	i++;
	if(i == key){
		cout<<root->data<<" ";
		return;
	}
	inorder(root->right,i,key);
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
	//cout << kthMIN(root,i,k);
	//or
	inorder(root,i,k);
	return 0;
}
