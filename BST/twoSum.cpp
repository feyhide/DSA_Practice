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

void twoSum(vector<int> ans,int target){
	int i = 0;
	int j = ans.size() - 1;
	int sum = 0;
	while(i != j){
		sum = ans[i] + ans[j];
		if(sum == target){
			cout<<ans[i]<<" "<<ans[j]<<endl;
			return;
		}
		else if(sum > target){
			j--;		
		}else{
			i++;
		}
	}
	cout<<"nope"<<endl;
	return;
}

void inorderTrav(vector<int>& ans,node* root){
	if(root == NULL){
		return;
	}
	inorderTrav(ans,root->left);
	ans.push_back(root->data);
	inorderTrav(ans,root->right);
}

void twoSumSolve(node* root,int target){
	vector<int> inorder;
	inorderTrav(inorder,root);
	twoSum(inorder,target);
}

int main(){
	node* root = NULL;
	
	cout << "enter data to create bst" << endl;
	
	takeInput(root);
	cout<<endl;
	levelOrderTraversal(root);
	cout<<endl;
	
	twoSumSolve(root,20);
	return 0;
}
