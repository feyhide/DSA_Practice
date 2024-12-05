#include<iostream>

using namespace std;

int calcPower(int base,int n){
	if(n == 0){
		return 1;
	}
	if(n == 1){
		return base;
	}
	if(n%2 == 0){
		return calcPower(base,n/2)*calcPower(base,n/2);
	}else{
		return base*calcPower(base,n/2)*calcPower(base,n/2);
	}
}

int main(){
	cout<<calcPower(2,10)<<endl;
	return 0;
}
