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

bool validBst(Node* root, int min,int max){
	if(root == NULL){
		return true;
	}
	
	if(root->data <= max && root->data >= min){
		int left = validBst(root->left,min,root->data);
		int right = validBst(root->left,root->data,max);
		return left && right;	
	}
	
	return false;
}

int main(){
	Node* root = NULL;
	root = createTree(root);
	levelOrderTraversal(root);
	cout<<endl;
	cout << validBst(root,INT_MIN,INT_MAX);
	return 0;
}
