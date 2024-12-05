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

void traverseLeft(Node* root,vector<int> &ans){
	if(root == NULL){
		return;
	}
	traverseLeft(root->left,ans);
	ans.push_back(root->data);
}

void traverseRight(Node* root,vector<int> &ans){
	if(root == NULL){
		return;
	}
	ans.push_back(root->data);
	traverseRight(root->right,ans);
}

vector<int> printTopView(Node* root){
	vector<int> ans;
	if(root == NULL){
		return ans;
	}
	traverseLeft(root->left,ans);
	ans.push_back(root->data);
	traverseRight(root->right,ans);
	return ans;
}

//also
vector<int> topView(Node* root){
	vector<int> ans;
	if(root == NULL){
		return ans;
	}
	
	map<int,int> topNode;
	queue<pair<Node*,int> > q;
	
	q.push(make_pair(root,0));
	
	while(!q.empty()){
		pair<Node*,int> temp = q.front();
		q.pop();
		Node* frontNode = temp.first;
		int hd = temp.second;
		
		if(topNode.find(hd) == topNode.end()){
			topNode[hd] = frontNode->data;
		}
		
		if(frontNode->left){
			q.push(make_pair(frontNode->left,hd-1));
		}
		
		if(frontNode->right){
			q.push(make_pair(frontNode->right,hd+1));
		}
	}
	
	for(auto it : topNode){
        ans.push_back(it.second);
    }
	
	return ans;
}

int main(){
	Node* root = NULL;
	root = createTree(root);
	levelOrderTraversal(root);
	cout<<endl;
	//vector<int> ans = printTopView(root);
	vector<int> ans = topView(root);
	for(int i = 0; i < ans.size(); i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}
