#include <bits/stdc++.h>
using namespace std;
#define FOR(x, y, z) for(int x = y; x <= z; x++)
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define all(x) x.begin(), x.end()
#define endl "\n"
#define x1 lol
#define y1 lal
#define sz(x) (int)(x.size())
#define ex exit(0)
#define PI 3.14159265359
typedef long long ll;
typedef pair<ll,ll> pii;
typedef vector<ll> vi;
double sqr(double x){return x*x;}
int const N=(int)2e6+1,INF=(int)1e9+1, MOD=(int)1e9+7;
ll mypow(ll a, ll b, ll mod) {
    ll rv = 1;
    while (b) {
        if (b % 2)
            rv = rv*a%mod;
        a = a*a %mod;
        b /= 2;
    }
    return rv;
}
int ans;
ll n;
bool sortbyX(pair<pair<int,int>, char> a, pair<pair<int,int>, char> b){
    return a.f.f < b.f.f;
}
bool sortbyY(pair<pair<int,int>, char> a, pair<pair<int,int>, char> b){
    return a.f.s < b.f.s;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
   // freopen("task2-test-input.txt", "r", stdin);
    //freopen("task2-test-output.txt", "w", stdout);
    cin>>n;
    vector<pair<pair<int,int>, char>> p(n);
    int cntb = 0, cnta = 0;
    for(int i = 0; i < n; i++){
        cin>>p[i].f.f>>p[i].f.s>>p[i].s;
        if(p[i].s == 'b')
            cntb++;
        else
            cnta++;
    }
    sort(p.begin(), p.end(), sortbyX);
    int i = 0;
    int tmpb = 0, tmpa = 0;
    while(i < n){
        ans = max(ans, max(cntb - tmpb + tmpa, cnta - tmpa + tmpb));
        if(p[i].s == 'w')
            tmpa++;
        else
            tmpb++;
        while(i + 1 < n && p[i].f.f == p[i+1].f.f){
            i++;
            if(p[i].s == 'w')
                tmpa++;
            else
                tmpb++;
        }
        i++;
    }
    sort(p.begin(), p.end(), sortbyY);
    i = 0;
    tmpb = 0; tmpa = 0;
    while(i < n){
        ans = max(ans, max(cntb - tmpb + tmpa, cnta - tmpa + tmpb));
        if(p[i].s == 'w')
            tmpa++;
        else
            tmpb++;
        while(i + 1 < n && p[i].f.s == p[i+1].f.s){
            i++;
            if(p[i].s == 'w')
                tmpa++;
            else
                tmpb++;
        }
        i++;
    }
    cout<<ans;
    return 0;
}

/*
0 1 1 2 2

*/