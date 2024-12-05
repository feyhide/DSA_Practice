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

Node* solve(int in[],int pre[],int &preOrderIndex,int inOrderStart,int inOrderEnd,int n){
	if (inOrderStart > inOrderEnd || preOrderIndex >= n) {
        return NULL;
    }
	int element = pre[preOrderIndex++];
	Node* root = new Node(element);
	int pos = findPos(in,element,n);	
	
	root->left = solve(in,pre,preOrderIndex,inOrderStart,pos-1,n);
	root->right = solve(in,pre,preOrderIndex,pos+1,inOrderEnd,n);
	return root;
}

Node* buildTree(int in[],int pre[],int n){
	int preOrderIndex = 0;
	Node* ans = solve(in,pre,preOrderIndex,0,n-1,n);
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
	int in[6] = {3,1,4,0,5,2};
	int pre[6] = {0,1,3,4,2,5};
	
	Node* root = buildTree(in,pre,6);
	levelOrderTraversal(root);
	return 0;
}
