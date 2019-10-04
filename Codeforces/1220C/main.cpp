#include <bits/stdc++.h>
 
using namespace std;
 
int main(){
	string s; 
	cin >> s;
	if (s.size()==1){
		cout << "Mike\n";
		return 0;
	}
	cout << "Mike\n";
	char x = s[0];
	for(int i = 1; i < s.size(); i++){
		int check = 0;
		if (s[i] > x){
			cout << "Ann\n";
			check = 1;
		}
		if (x > s[i]){
			x = s[i];
		}
		if (!check) cout << "Mike\n";
		if (!check) continue;
		
	}
	
 
 
	return 0;
}
