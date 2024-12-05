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

vector<int> printBottomView(Node* root){
	vector<int> ans;
	if(root == NULL){
		return ans;
	}
	
	map<int,int> bottomNode;
	queue<pair<Node*,int> > q;
	
	q.push(make_pair(root,0));
	
	while(!q.empty()){
		pair<Node*,int> temp = q.front();
		q.pop();
		Node* frontNode = temp.first;
		int hd = temp.second;
		
		bottomNode[hd] = frontNode->data;
		
		if(frontNode->left){
			q.push(make_pair(frontNode->left,hd-1));
		}
		
		if(frontNode->right){
			q.push(make_pair(frontNode->right,hd+1));
		}
	}
	
	for(auto it : bottomNode){
        ans.push_back(it.second);
    }
	
	return ans;
}

int main(){
	Node* root = NULL;
	root = createTree(root);
	levelOrderTraversal(root);
	cout<<endl;
	vector<int> ans = printBottomView(root);
	
	for(int i = 0; i < ans.size(); i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}
