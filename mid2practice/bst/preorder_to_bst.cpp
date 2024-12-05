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

node* solve(vector<int>& preorder,int mini,int maxi,int& i){
	if(i>=preorder.size()){
		return NULL;
	}
	if(preorder[i] < mini || preorder[i] > maxi){
		return NULL;
	}
	
	node* root = new node(preorder[i++]);
	root->left = solve(preorder,mini,root->data,i);
	root->right = solve(preorder,root->data,maxi,i);
	return root;
}

node* preorderToBst(vector<int>& preorder){
	int mini = INT_MIN;
	int maxi = INT_MAX;
	int i = 0;
	return solve(preorder,mini,maxi,i);
}

int main(){
	vector<int> preorder;
	cout << "enter data for preorder: ";
    int data;
    cin >> data;
    while (data != -1) {
        preorder.push_back(data);
        cin >> data;
    }
	node* root = preorderToBst(preorder);
	cout<<endl;
	levelOrderTraversal(root);
	cout<<endl;
	
	return 0;
}
