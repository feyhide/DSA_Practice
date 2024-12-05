#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;
    
    Node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }
};

int getHeight(Node* root) {
    if (!root) {
        return 0;
    }
    return root->height;
}

int getBalanceFactor(Node* root) {
    if (!root) {
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);
}

Node* leftRotate(Node* y) {
    Node* x = y->right;
    Node* t2 = x->left;
    
    x->left = y;
    y->right = t2;
    
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    
    return x;
}

Node* rightRotate(Node* x) {
    Node* y = x->left;
    Node* t2 = y->right;
    
    y->right = x;
    x->left = t2;
    
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    
    return y;
}

Node* insert(Node* root, int key) {
    if (root == NULL) {
        return new Node(key);
    }
    if (key < root->data) {
        root->left = insert(root->left, key);
    } else if (key > root->data) {
        root->right = insert(root->right, key);
    } else {
        return root;
    }
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);
    
    if (bf > 1 && key < root->left->data) {
        return rightRotate(root);
    }
    if (bf < -1 && key > root->right->data) {
        return leftRotate(root);
    }
    if (bf > 1 && key > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && key < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* minValueNode(Node* root) {
    Node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    
    if (root == NULL) {
        return root;
    }
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);
    
    if (bf > 1 && getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }
    if (bf > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }
    if (bf < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

void preOrder(Node* root) {
    if (root != NULL) {
        preOrder(root->left);
        cout << root->data << " ";
        preOrder(root->right);
    }
}

int main() {
    Node* root = NULL;
    
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    
    cout << "Preorder traversal of the AVL tree is: ";
    preOrder(root);
    cout << endl;
    
    root = deleteNode(root, 30);
    
    cout << "Preorder traversal after deletion of 30: ";
    preOrder(root);
    cout << endl;
    
    int key = 25;
    Node* found = search(root, key);
    if (found) {
        cout << "Node " << key << " found in the tree.\n";
    } else {
        cout << "Node " << key << " not found in the tree.\n";
    }
    
    return 0;
}

