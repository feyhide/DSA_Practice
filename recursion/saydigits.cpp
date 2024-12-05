#include<iostream>

using namespace std;

string arr[10] = {"one","two","three","four","five","six","seven","eight","nine","ten"};

void sayDigits(int n){
	if(n <= 0){
		return;
	}
	sayDigits(n/10);
	cout<<arr[(n%10)-1]<<" ";
}

int main(){
	sayDigits(19);
	return 0;
}
