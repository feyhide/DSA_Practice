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

void buildFromLevelOrder(Node* &root){
	queue<Node*> q;
	cout<< "enter data for root : ";
	int data;
	cin>>data;
	root = new Node(data);
	q.push(root);
	
	while(!q.empty()){
		Node* temp = q.front();
		q.pop();
		
		cout << "enter left value to " << temp->data << " : ";
		int leftData;
		cin>>leftData;
		
		if(leftData != -1){
			temp->left = new Node(leftData);
			q.push(temp->left);
		}
		
		cout << "enter right value to " << temp->data << " : ";
		int rightData;
		cin>>rightData;
		
		if(rightData != -1){
			temp->right = new Node(rightData);
			q.push(temp->right);
		}
	}
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

int main(){
	Node* root = NULL;
	buildFromLevelOrder(root);
	levelOrderTraversal(root);
	return 0;
}
