#include <bits/stdc++.h>
 
using namespace std;
 
int main(){
	int n;
	cin >> n;
	long long arr[n][n];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> arr[i][j];
		}
	}
	long long x1 = sqrt(arr[0][1]*arr[0][2]/arr[1][2]);
	long long x2 = x1;
	cout << x1 << " ";
	for(int i = 1; i < n; i++){
		x2 = arr[0][i]/x1;
		cout << x2 << " ";
	}
 
 
	return 0;
}
