#include <bits/stdc++.h>
 
using namespace std;
 
int main(){
	int n;
	cin >> n;
	string s;
	cin >> s;
	int num1 = 0;
	int num2 = 0;
	for(int i = 0; i < n; i++){
		if (s[i]=='n') num1++;
		if (s[i]=='z') num2++;
	}
 
	for(int i = 0; i < num1;i++){
		cout << 1 << " ";
	}
	for(int i = 0; i < num2; i++){
		cout << 0 << " ";
	}
 
 
	return 0;
}
