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

bool identical(Node* r1,Node* r2){
	if(r1 == NULL && r2 == NULL){
		return true;
	}
	if(r1 == NULL && r2 != NULL){
		return false;
	}
	if(r1 != NULL && r2 == NULL){
		return false;
	}
	bool left = identical(r1->left,r2->left);
	bool right = identical(r1->right,r2->right);
	
	bool value = r1->data == r2->data;
	if(left && right && value){
		return true;
	}else{
		return false;
	}
}


int main(){
	Node* r1 = NULL;
	root = createTree(r1);
	
	Node* r2 = NULL;
	root = createTree(r2);
	levelOrderTraversal(r1);
	cout<<endl;
	levelOrderTraversal(r2);
	cout<<endl<<identical(r1,r2);
	return 0;
}
