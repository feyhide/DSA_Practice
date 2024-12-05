#include<iostream>
#include<queue>
#include<stack>
#include<vector>
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

vector<int> zigZagTraversal(Node* root){
	vector<int> result;
	
	if(root == NULL){
		return result;
	}
	queue<Node*> q;
	q.push(root);
	
	bool leftToRight = true;
	
	while(!q.empty()){
		int size = q.size();
		vector<int> ans(size);
		
		for(int i = 0; i < size; i++){
			Node* frontNode = q.front();
			q.pop();
			
			int index = leftToRight ? i : size-i-1;
			ans[index] = frontNode->data;
			if(frontNode->left){
				q.push(frontNode->left);
			}
			if(frontNode->right){
				q.push(frontNode->right);
			}
		}
		
		leftToRight = !leftToRight;
		
		for(int i = 0; i < ans.size(); i++){
			result.push_back(ans[i]);
		}
	}
	return result;
}

int main(){
	Node* root = NULL;
	root = createTree(root);
	levelOrderTraversal(root);
	
	vector<int> tree = zigZagTraversal(root);
	
	for(int i = 0; i < tree.size(); i++){
		cout<<tree[i]<<" ";
	}
	return 0;
}
