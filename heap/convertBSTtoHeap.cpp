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

void reverseOrderTraversal(Node* root) {
    if (root == NULL) return;

    queue<Node*> q;
    stack<Node*> s;

    q.push(root);
    q.push(NULL); 

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp == NULL) {
            s.push(NULL); 
            if (!q.empty()) {
                q.push(NULL); 
            }
        } else {
            s.push(temp);
            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
        }
    }

    while (!s.empty()) {
        Node* node = s.top();
        s.pop();

        if (node == NULL) {
            cout << endl;
        } else {
            cout << node->data << " ";
        }
    }
    cout << endl;
}

void inorder(Node* root, vector<int>& ans){
	if(root == NULL){
		return;
	}
	
	inorder(root->left,ans);
	ans.push_back(root->data);
	inorder(root->right,ans);
}


void convertBSTtoHeap(Node* root, vector<int>& sortedValues) {
    if (root == NULL) return;

    queue<Node*> q;
    q.push(root);

    int index = 0;

    while (!q.empty() && index < sortedValues.size()) {
        Node* current = q.front();
        q.pop();

        current->data = sortedValues[index++];
        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
}

int main(){
	Node* root = NULL;
	root = createTree(root);
	levelOrderTraversal(root);
	
	cout << endl;
	
	vector<int> _inorder;
	inorder(root,_inorder);
	convertBSTtoHeap(root,_inorder);
	
	levelOrderTraversal(root);
	return 0;
}
