#include<iostream>
#include<queue>
#include<stack>

using namespace std;

class Node{
	public:
		int data;
		Node* left;
		Node* right;
		
		Node(int data){
			this->data = data;
			this->left = NULL;
			this->right = NULL;
		}
};

Node* createTree(Node* root){
	cout<< "enter data : "<< endl;
	int data;
	cin>>data;
	root = new Node(data);
	
	if(data == -1){
		return NULL;
	}
	
	cout << "Enter data for inserting in left of " << data << endl;
	root->left = createTree(root->left);
	cout << "Enter data for inserting in right of " << data << endl;
	root->right = createTree(root->right);
	return root;
}

void levelOrderTraversal(Node* root){
	queue<Node*> q;
	q.push(root);
	q.push(NULL);
	while(!q.empty()){
		Node* temp = q.front();
		q.pop();
		
		if(temp == NULL){
			cout<<endl;
			if(!q.empty()){
				q.push(NULL);
			}
		}else{
			cout << temp->data << " ";
			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}
	}
}

void traverseLeft(Node* root, vector<int> &ans){
	if((root == NULL) || (root->left == NULL && root->right == NULL)){
		return;
	}
	
	ans.push_back(root->data);
	
	if(root->left){
		traverseLeft(root->left,ans);
	}else{
		traverseLeft(root->right,ans);
	}
}

void traverseRight(Node* root, vector<int> &ans){
	if((root == NULL) || (root->left == NULL && root->right == NULL)){
		return;
	}
	
	if(root->right){
		traverseRight(root->right,ans);
	}else{
		traverseRight(root->left,ans);
	}
	ans.push_back(root->data);
}

void traverseLeaf(Node* root, vector<int> &ans){
	if(root == NULL){
		return;
	}
	
	if(root->left == NULL && root->right == NULL){
		ans.push_back(root->data);
		return;
	}
		
	traverseLeaf(root->left,ans);
	traverseLeaf(root->right,ans);
}

vector<int> boundary(Node* root){
	vector<int> ans;
	if(root==NULL){
		return ans;
	}
	ans.push_back(root->data);
	
	traverseLeft(root->left,ans);
	
	traverseLeaf(root->left,ans);
	traverseLeaf(root->right,ans);
	
	traverseRight(root->right,ans);
	
	return ans;
}


int main(){
	Node* root = NULL;
	root = createTree(root);
	levelOrderTraversal(root);
	
	vector<int> ans = boundary(root);
	
	for(int i = 0; i < ans.size(); i++){
		cout<<ans[i]<<" ";
	}
	return 0;
} 
