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

int findPos(int in[],int el,int n){
	for(int i = 0; i < n; i++){
		if(in[i] == el){
			return i;
		}
	}
	return -1;
}

Node* solve(int in[],int post[],int &postOrderIndex,int inOrderStart,int inOrderEnd,int n){
	if (postOrderIndex < 0 || inOrderStart > inOrderEnd) {
        return NULL;
    }
	int element = post[postOrderIndex--];
	Node* root = new Node(element);
	int pos = findPos(in,element,n);
	
	root->right = solve(in,post,postOrderIndex,pos+1,inOrderEnd,n);
	root->left = solve(in,post,postOrderIndex,inOrderStart,pos-1,n);
	
	return root;
}

Node* buildTree(int in[],int post[],int n){
	int postOrderIndex = n-1;
	Node* ans = solve(in,post,postOrderIndex,0,n-1,n);
	return ans;
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
	int in[8] = {4,8,2,5,1,6,3,7};
	int post[8] = {8,4,5,2,6,7,3,1};
	
	Node* root = buildTree(in,post,8);
	levelOrderTraversal(root);
	return 0;
}
