#include<iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

int count(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + count(root->left) + count(root->right);
}

bool isCBT(Node* root, int index, int cnt) {
    if (root == NULL) {
        return true;
    }
    if (index >= cnt) {
        return false;
    }

    bool left = isCBT(root->left, 2 * index + 1, cnt);
    bool right = isCBT(root->right, 2 * index + 2, cnt);

    return left && right;
}

bool isMaxOrder(Node* root) {
    if (root->left == NULL && root->right == NULL) {
        return true;
    }

    if (root->right == NULL) {
        return root->data > root->left->data;
    }

    bool left = isMaxOrder(root->left);
    bool right = isMaxOrder(root->right);

    return left && right &&
           (root->data > root->left->data && root->data > root->right->data);
}

bool isHeap(Node* root) {
    int index = 0;
    int totalCount = count(root);

    return isCBT(root, index, totalCount) && isMaxOrder(root);
}

int main() {
    Node* root = new Node(15);
    root->left = new Node(9);
    root->right = new Node(8);
    root->left->left = new Node(7);
    root->left->right = new Node(6);

    if (isHeap(root)) {
        cout << "The tree is a heap" << endl;
    } else {
        cout << "The tree is not a heap" << endl;
    }

    return 0;
}

