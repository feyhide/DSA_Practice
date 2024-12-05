#include<iostream>
#include<stack>
#include<queue>
#include<map>

using namespace std;

class Node{
	public:
	int data;
	Node* left;
	Node* right;
	
	Node(int data){
		this->data =data;
		this->left = NULL;
		this->right = NULL;
	}
};

Node* createRoot(Node* root){
	if(root == NULL){
		cout<<" enter data: ";
	}
	
	
	int data;
	cin>>data;
	
	
	root = new Node(data);
	
	
	if(data == -1){
		return NULL;
	}

	cout<<"for left of "<<root->data;
	root->left = createRoot(root->left);
	cout<<"for right of "<<root->data;
	root->right = createRoot(root->right);
	return root;
}

void levelorder(Node* root){
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
			cout<<temp->data<<" ";
			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}
	}
	cout<<endl;
}

void reverseorder(Node* root){
	queue<Node*> q;
	stack<Node*> s;
	q.push(root);
	q.push(NULL);
	
	while(!q.empty()){
		Node* temp = q.front();
		q.pop();
		if(temp == NULL){
			s.push(NULL);
			if(!q.empty()){
				q.push(NULL);
			}
		}else{
			s.push(temp);
			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}
	}
	
	while(!s.empty()){
		Node* temp = s.top();
		s.pop();
		if(temp==NULL){
			cout<<endl;
		}else{
			cout<<temp->data<<" ";
		}
	}
	cout<<endl;
}

void inorderTraversal(Node* root){
	if(root == NULL){
		return;
	}
	
	inorderTraversal(root->left);
	cout<<root->data<<endl;
	inorderTraversal(root->right);
}

void preorderTraversal(Node* root){
	if(root == NULL){
		return;
	}
	
	cout<<root->data<<endl;
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

void postorderTraversal(Node* root){
	if(root == NULL){
		return;
	}
	
	postorderTraversal(root->left);
	postorderTraversal(root->right);
	cout<<root->data<<endl;
}

void _topView(Node* root){
	if(root == NULL){
		return;
	}
	vector<int> ans;
	map<int,int> topView;
	queue<pair<Node*,int> > q;
	
	q.push(make_pair(root,0));
	
	while(!q.empty()){
		pair<Node*,int> p = q.front();
		Node* frontNode = p.first;
		int hd = p.second;
		q.pop();
		
		if(topView.find(hd) == topView.end()){
			topView[hd] = frontNode->data;
		}
		
		if(frontNode->left){
			q.push(make_pair(frontNode->left,hd-1));
		}
		
		if(frontNode->right){
			q.push(make_pair(frontNode->right,hd+1));
		}
	}
	
	for(auto it: topView){
		ans.push_back(it.second);
	}
}

void _bottomView(Node* root){
	if(root == NULL){
		return;
	}
	vector<int> ans;
	map<int,int> bottomView;
	queue<pair<Node*,int> > q;
	
	q.push(make_pair(root,0));
	
	while(!q.empty()){
		pair<Node*,int> p = q.front();
		Node* frontNode = p.first;
		int hd = p.second;
		q.pop();
		
		bottomView[hd] = frontNode->data;
		
		if(frontNode->left){
			q.push(make_pair(frontNode->left,hd-1));
		}
		
		if(frontNode->right){
			q.push(make_pair(frontNode->right,hd+1));
		}
	}
	
	for(auto it: bottomView){
		ans.push_back(it.second);
	}
}




int main(){
	Node* root = NULL;
	root = createRoot(root);
	levelorder(root);
	reverseorder(root);
	return 0;
}
