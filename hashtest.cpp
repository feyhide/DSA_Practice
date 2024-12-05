#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
	int key = 12;
	int size = 5;
	
	
	//division
	cout<<key%size<<endl; 
	
	//mid square
	long long sq = key*key;
	string toFindLen = to_string(sq);
	long long len = toFindLen.length();
	long long divisor = 10*len;
	cout<<((sq/divisor)%divisor)%size<<endl;
	
	//multiplying'
	const float A = 0.6180339887;
	float product = key * A;
	float fractionalPart = product - floor(product);
	cout<<floor(size*fractionalPart)<<endl;
	
    return 0;
}

