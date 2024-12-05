#include <iostream>
#include <stack>
using namespace std;

class Stack{
	public:
		int top1;
		int top2;
		int *arr;
		int size;
		
		
	Stack(int size){
		this->size = size;
		this->top1 = -1;
		this->top2 = size;
		this->arr = new int[size];
	}
	
	void push1(int data){
		if(top2-top1 > 1){
			top1++;
			arr[top1] = data;
		}else{
			cout<<"overflowed"<<endl;
		}
	}
	void push2(int data){
		if(top2-top1 > 1){
			top2--;
			arr[top2] = data;
		}else{
			cout<<"overflowed"<<endl;
		}
	}
	
	int pop1(){
		if(top1>=0){
			int ans = arr[top1];
			top1--;
			return ans;
		}else{
			cout<<"underflowed"<<endl;
		}
	}
	int pop2(){
		if(top2 < size){
			int ans = arr[top2];
			top2++;
			return ans;
		}else{
			cout<<"underflowed"<<endl;
		}
	}
};	


int main(){
	Stack st(5);
	st.push1(1);
	st.push1(2);
	st.push1(3);
	st.push2(2);
	st.push2(1);
	st.push2(0);
	st.push1(0);
	st.pop1();
	st.pop1();
	st.pop1();
	st.pop1();
	
	st.pop2();
	st.pop2();
	st.pop2();
	return 0;
}
