#include <iostream>
using namespace std;

class Node{
    public:
    int data;
    Node* next;
    
    Node(int data){
        this->data = data;
        this->next = NULL;
    }
};

Node* mergeSort(Node* first, Node* second){
    if(first == NULL){
        return second;
    }
    if(second == NULL){
        return first;
    }
    Node* tempHead = new Node(-1);
    Node* temp = tempHead;
	while(first!=NULL && second!=NULL){
        if(first->data < second->data){
        	temp->next = first;
			first = first->next;
		}else{
			temp->next = second;
			second = second->next;
		}
		temp = temp->next;
    }
    
    if(first!=NULL){
		temp->next = first;
	}
	if(second!=NULL){
		temp->next = second;
	}
	Node* mergedHead = tempHead->next;
    delete tempHead; 
    return mergedHead;
}

Node* getMid(Node* start){
	if(start == NULL){
		return NULL;
	}
	Node* slow = start;
	Node* fast = start->next;
	while(fast != NULL && fast->next != NULL){
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

Node* merge(Node* start){
	if(start == NULL || start->next == NULL){
		return start;
	}
	Node* mid = getMid(start);
	Node* left = start;
	Node* right = mid->next;
	mid->next = NULL;
	
	left = merge(left);
	right = merge(right);
	
	return mergeSort(left,right);
}

void print(Node* start){
	Node* temp = start;
	while(temp != NULL){
		cout<<temp->data<<" ";
		temp=temp->next;
	}
}

int main() {
    
	Node* start = new Node(4);
	start->next = new Node(3);
	start->next->next = new Node(2);
	start->next->next->next = new Node(1);
	start->next->next->next->next = new Node(6);
	print(start);
	cout<<endl;
	Node* merged = merge(start);
	print(merged);
    return 0;
}
