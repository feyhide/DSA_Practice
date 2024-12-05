#include <iostream>
#include <stack>
using namespace std;

class Stack{
	public:
		int top;
		int *arr;
		int size;
		
	Stack(int size){
		this->size = size;
		this->arr = new int[size];
		this->top = -1;
	}
	
	void push(int data){
		if(size-top > 1){
			top++;
			arr[top] = data;
		}else{
			cout<<"Stack is full"<<endl;
		}
	}
	
	void pop(){
		if(top>=0){
			top--;
		}else{
			cout<<"Stack is empty already"<<endl;
		}
	}
	
	int peek(){
		if(top>=0 && top<size){
			return arr[top];
		}else{
			cout<<"Stack is empty"<<endl;
		}
	}
	
	bool isEmpty(){
		if(top == -1){
			return true;
		}else{
			return false;
		}
	}
	
	int stacksize(){
		if(top >= 0){
			return top+1;
		}else{
			cout<<"Stack is empty"<<endl;
		}
	}
};	


int main(){
	Stack st(5); // size of array is 5
	st.push(22);
	cout<<"stack size:"<<st.stacksize()<<endl;
	st.push(43);
	cout<<"stack size:"<<st.stacksize()<<endl;
	st.push(101);
	cout<<"stack size:"<<st.stacksize()<<endl;
	cout<<st.peek()<<endl;
	st.pop();
	cout<<st.peek()<<endl;
	st.pop();
	cout<<st.peek()<<endl;
	cout<<"empty:"<<st.isEmpty()<<endl;
	cout<<"stack size:"<<st.stacksize()<<endl;
	st.pop();
	st.push(22);
	st.push(22);
	st.push(22);
	st.push(22);
	st.push(22);
	st.push(22);
	
	st.pop();
	st.pop();
	st.pop();
	st.pop();
	st.pop();
	st.pop();
	return 0;
}
