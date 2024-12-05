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

node* link(vector<node*>& inorder){
	for(int i = 0; i < inorder.size()-1; i++){
		inorder[i]->left = NULL;
		inorder[i]->right = inorder[i+1];
	}
	inorder.back()->right = NULL;
	return inorder[0];
}

void inorderTrav(vector<node*>& ans,node* root){
	if(root == NULL){
		return;
	}
	inorderTrav(ans,root->left);
	ans.push_back(root);
	inorderTrav(ans,root->right);
}

void print(node* root){
	node* temp = root;
	while(temp){
		cout<<temp->data << " ";
		temp = temp->right;
	}
}

void flatten(node* root){
	vector<node*> inorder;
	inorderTrav(inorder,root);
	root = link(inorder);
	print(root);
}

int main(){
	node* root = NULL;
	
	cout << "enter data to create bst" << endl;
	
	takeInput(root);
	cout<<endl;
	levelOrderTraversal(root);
	cout<<endl;
	flatten(root);
	return 0;
}
