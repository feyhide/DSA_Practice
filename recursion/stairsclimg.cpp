#include<iostream>

using namespace std;

int stairClimb(int n){
	if(n<0){
		return 0;
	}
	if(n==0){
		return 1;
	}
	return stairClimb(n-1)+stairClimb(n-2);
}

//for understanding
int howmanysubtraction(int n){
	if(n<0){
		return 0;
	}
	if(n==0){
		return 1;
	}
	return howmanysubtraction(n-1)+howmanysubtraction(n-2);
}

int main(){
	cout<<stairClimb(4)<<endl;
	cout<<howmanysubtraction(4)<<endl;
	return 0;
}

