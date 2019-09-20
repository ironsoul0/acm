//By Nurbergen Hinatolla
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>  
#include <stdio.h>
#include <cstdio>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <cmath>
#include <math.h>
#include <map>
#include <set>
#include <time.h>
#include <bitset>

#define INF 1000000000000000000LL
#define inf 2147483647
#define MOD 1000000000
#define pf push_front
#define pb push_back
#define mp make_pair
#define FI first
#define SI second
#define fname "" 
                                
using namespace std;

typedef long long ll;

map <int, bool> X;

struct node {
	node *l;
	node *r;
	int key, y, cnt; 
	node() {
		y = rand();
		cnt = 1;
		l = r = nullptr;
	}
}; 

typedef node* pnode;

pnode root, A, B, _x, C;

void out(pnode t) {
	if (!t) {
		return;
	}
	out(t -> l);
	cout << t -> key << " ";
	out(t -> r);
}

int get_cnt(pnode v) {
	return v ? v -> cnt : 0;
}
 
void update(pnode v) {
    if (!v) {
        return;
    }
    v -> cnt = get_cnt(v -> l) + get_cnt(v -> r) + 1;
}
void Split(pnode v, pnode &A, pnode &B, int x, int now = 0) {
    if (!v) {
        return void(A = B = NULL);
    }
    int cur = now + get_cnt(v -> l) + 1;
    if (cur <= x) {
        Split(v -> r, v -> r, B, x, now + get_cnt(v -> l) + 1);
        A = v;

    }
    else {
        Split(v -> l, A, v -> l, x, now);
        B = v; 
    }
    update(v);
}
void split(pnode v, pnode &A, pnode &B, int x) {
     if (!v)
        return void(A = B = 0);
     if (v -> key <= x) {
        split(v -> r, v -> r, B, x);
        A = v;
     } else {
        split(v -> l, A, v -> l, x);        
        B = v;
     }
     update(v);
}
pnode _merge(pnode A, pnode B) {
    if (!A || !B) {
       return (A == NULL ? B : A);
    }
    if (A -> y > B -> y) {
       A -> r = _merge(A -> r, B);    
       update(A);
       return A;
    } else {
       B -> l = _merge(A, B -> l);
       update(B);
       return B; 
    } 
}         

void add(int x) { 
	A = B = C = NULL; 
	_x = new node(); 
	_x -> key = x;
    split(root, A, B, x - 1);
    root = _merge(_merge(A, _x), B);
}
void del(int x) { 
	A = B = C = NULL; 
    split(root, A, B, x - 1);
    split(B, B, C, x);
    root = _merge(A, C);
}
int main() {
    srand(259);
  //	#ifndef ONLINE_JUDGE
  //  	freopen(fname".in", "r", stdin);
  //  	freopen(fname".out", "w", stdout);
  //  #endif
    int x;
    string ch;
    root = NULL;
    while (cin >> ch >> x) {
        if (ch == "insert") { 
            if (!X[x])
            	add(x), X[x] = true;
        }
        if (ch == "delete") { 
            if (X[x])
            	del(x), X[x] = false;
        }
        if (ch == "exists") {
        	A = B = C = NULL; 
		    split(root, A, B, x - 1);
		    split(B, B, C, x);
		    if (!B)
		    	printf("false\n");
		    else
		    	printf("true\n");
    		root = _merge(_merge(A, B), C);
            }
        if (ch == "next") {
        	A = B = C = NULL; 
		    split(root, A, B, x);
		    Split(B, B, C, 1);
		    if (!B)
		    	printf("none\n");
		  	else
		  		printf("%d\n", B -> key);	
        	root = _merge(_merge(A, B), C);
        }
        if (ch == "prev") {
        	A = B = C = NULL; 
		    split(root, A, C, x - 1);
		    if (!A) {
		    	printf("none\n");
		    	root = _merge(A, C);
		    	continue;
		    }
		    Split(A, A, B, A -> cnt - 2);
		    if (!B)
		    	printf("none\n");
		  	else
		  		printf("%d\n", B -> key);	
        	root = _merge(_merge(A, B), C);
        }
        if (ch == "kth") {
        	A = B = C = NULL; 
            Split(root, A, B, x - 1);
            Split(B, B, C, x);
            if (!B)
		    	printf("none\n");
		  	else
		  		printf("%d\n", B -> key);	
        	root = _merge(_merge(A, B), C);
        }
    }
    
    return 0;
}
