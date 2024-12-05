#include<iostream>
#include<queue>
#include<stack>
#include<map>

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

void solve(Node* root,vector<int> &ans,int level){
	if(root == NULL){
		return ;
	}
	
	if(level == ans.size()){
		ans.push_back(root->data);
	}
	
	solve(root->left,ans,level+1);
	solve(root->right,ans,level+1);
}

vector<int> leftView(Node* root){
	vector<int> ans;
	
	solve(root,ans,0);
	
	return ans;
}

int main(){
	Node* root = NULL;
	root = createTree(root);
	levelOrderTraversal(root);
	cout<<endl;
	vector<int> ans = leftView(root);
	for(int i = 0; i < ans.size(); i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}
