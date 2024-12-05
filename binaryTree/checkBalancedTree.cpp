#include<iostream>
#include<queue>
#include<stack>

// height of left - height of right < = 1

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

int height(Node* root){
	if(root == NULL){
		return 0;
	}
	int left = height(root->left);
	int right = height(root->right);
	
	int ans = max(left,right)+1;
	return ans;
}

bool checkBalanced(Node* root){
	if(root == NULL){
		return true;
	}	
	
	bool left = checkBalanced(root->left);
	bool right = checkBalanced(root->right);
	bool diff = abs(height(root->left) - height(root->right)) <= 1;
	
	if(left && right && diff){
		return true;
	}else{	
		return false;
	}
}

pair<bool,int> checkBalancedFast(Node* root){
	if(root == NULL){
		pair<int,int> p = make_pair(true,0);
		return p;
	}	
	
	pair<bool,int> left = checkBalancedFast(root->left);
	pair<bool,int> right = checkBalancedFast(root->right);
	
	bool leftAns = left.first;
	bool rightAns = right.first;
	
	bool diff = abs(left.second - right.second) <= 1;
	
	pair<bool,int> ans;	
	ans.second = max(left.second,right.second) + 1;
	
	if(leftAns && rightAns && diff){
		ans.first = true;
	}else{
		ans.first = false;
	}
	return ans;
}


int main(){
	Node* root = NULL;
	root = createTree(root);
	levelOrderTraversal(root);
	cout << endl << checkBalanced(root);
	cout << endl << checkBalancedFast(root).first;
	return 0;
}
