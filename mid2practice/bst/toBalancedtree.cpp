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


void inorderTrav(vector<int>& ans,node* root){
	if(root == NULL){
		return;
	}
	inorderTrav(ans,root->left);
	ans.push_back(root->data);
	inorderTrav(ans,root->right);
}

node* toBBst(int s, int e, vector<int> inorder){
	if(s>e){
		return NULL;
	}
	
	int mid = (s+e)/2;
	node* root = new node(inorder[mid]);
	root->left = toBBst(s, mid-1, inorder);
	root->right = toBBst(mid+1, e, inorder);
	return root;
}

node* balanced(node* root){
	vector<int> inorder;
	inorderTrav(inorder,root);
	return toBBst(0,inorder.size()-1,inorder);
}

int main(){
	node* root = NULL;
	
	cout << "enter data to create bst" << endl;
	
	takeInput(root);
	cout<<endl;
	levelOrderTraversal(root);
	cout<<endl;
	root = balanced(root);
	cout<<endl;
	levelOrderTraversal(root);
	cout<<endl;
	
	return 0;
}
