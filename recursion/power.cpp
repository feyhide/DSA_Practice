#include<iostream>

using namespace std;

int power(int n,int base){
	if(n == 0){
		return 1;
	}
	return base*power(n-1,base);
}

int _power(int n,int base){
	if(n == 0){
		return 1;
	}
	int smallerProblem = _power(n-1,base);
	int biggerProblem = base * smallerProblem;
	
	return biggerProblem;
}


int main(){
	cout<<power(3,2)<<endl;
	cout<<_power(3,3)<<endl;
	return 0;
}
