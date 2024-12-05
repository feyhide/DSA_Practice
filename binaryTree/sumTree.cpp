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

pair<bool,int> checkSum(Node* root){
	if(root == NULL){
		pair<bool,int> p = make_pair(true,0);
		return p;
	}
	//dont check leafs
	if(root->left == NULL && root->right == NULL){
		pair<bool,int> p = make_pair(true,0);
		return p;
	}
	
	pair<bool,int> left = checkSum(root->left);
	pair<bool,int> right = checkSum(root->right);
	
	bool isLeftSumTree = left.first;
	bool isRightSumTree = right.first;
	
	int rightSum = right.second;
	int leftSum = left.second;
	
	bool cond = root->data == leftSum + rightSum;
	
	pair<bool,int> ans;
	
	if(isLeftSumTree && isRightSumTree && cond){
		ans.first = true;
		ans.second = root->data + rightSum + leftSum;
	}else{
		ans.first = false;
	}
	return ans;
}


int main(){
	Node* root = NULL;
	root = createTree(root);
	levelOrderTraversal(root);
	cout<<endl<<checkSum(root).first;
	return 0;
}
