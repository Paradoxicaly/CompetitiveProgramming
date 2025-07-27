/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;

#define pb push_back
#define fi first
#define se second
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0;i<(n);++i)
#define rng(i,a,b) for(int i=(a);i<(b);++i)

static int arr[300000];
static int pref[300001];
int startPos, endPos, pivotVal;

void findWindow(int n,int k){
    int lo=0, hi=n;
    while(hi-lo>1){
        int mid=(lo+hi+1)/2;
        pref[0]=0;
        rep(i,n) pref[i+1]=pref[i] + (arr[i] <= mid ? 1 : -1);
        int best=1e9;
        bool ok=false;
        for(int i=k;i<=n;i++){
            best = min(best, pref[i-k]);
            if(pref[i]-best >= 0){ ok=true; break; }
        }
        if(ok) hi=mid; else lo=mid;
    }
    pivotVal = hi;
    pref[0]=0;
    rep(i,n) pref[i+1]=pref[i] + (arr[i] <= hi ? 1 : -1);
    int best=1e9, pos=-1;
    for(int i=k;i<=n;i++){
        if(pref[i-k]<best){ best=pref[i-k]; pos=i-k; }
        if(pref[i]-best >= 0){
            startPos = pos;
            endPos = i;
            return;
        }
    }
}

map<int,int> low, high;
int szLow, szHigh;

int getMax(map<int,int>& M){
    while(!M.empty()){
        auto it = prev(M.end());
        if(it->se==0) M.erase(it);
        else return it->fi;
    }
    return -1000000000;
}
int getMin(map<int,int>& M){
    while(!M.empty()){
        auto it = M.begin();
        if(it->se==0) M.erase(it);
        else return it->fi;
    }
    return 1000000000;
}
void rebalance(){
    while(szHigh>szLow){
        int x = getMin(high);
        high[x]--; szHigh--;
        low[x]++; szLow++;
    }
    while(szLow>szHigh+1){
        int x = getMax(low);
        low[x]--; szLow--;
        high[x]++; szHigh++;
    }
}
bool isMedian(int x){
    if(szLow==szHigh){
        int m1 = getMax(low), m2 = getMin(high);
        return m1<=x && x<=m2;
    } else {
        return x==getMax(low);
    }
}
void addVal(int x){
    if(x<=getMax(low)){
        low[x]++; szLow++;
    } else {
        high[x]++; szHigh++;
    }
    rebalance();
}
void removeVal(int x){
    if(x<=getMax(low)){
        low[x]--; szLow--;
    } else {
        high[x]--; szHigh--;
    }
    rebalance();
}

void solve(){
    int n,k;
    cin>>n>>k;
    rep(i,n) cin>>arr[i];
    findWindow(n,k);
    int l1=startPos, r1=endPos, c1=pivotVal;
    rep(i,n) arr[i]=n-arr[i]+1;
    findWindow(n,k);
    int l2=startPos, r2=endPos, c2=n-pivotVal+1;
    rep(i,n) arr[i]=n-arr[i]+1;
    low.clear(); high.clear();
    szLow=szHigh=0;
    vector<array<int,3>> out;
    int v=c1;
    for(int i=l1;i<r1;i++) addVal(arr[i]);
    while(v<=c2 && isMedian(v)){
        out.pb({v,l1+1,r1});
        v++;
    }
    while(l1>l2){
        addVal(arr[--l1]);
        while(v<=c2 && isMedian(v)){
            out.pb({v,l1+1,r1});
            v++;
        }
    }
    while(r1<r2){
        addVal(arr[r1++]);
        while(v<=c2 && isMedian(v)){
            out.pb({v,l1+1,r1});
            v++;
        }
    }
    while(l1<l2){
        removeVal(arr[l1++]);
        while(v<=c2 && isMedian(v)){
            out.pb({v,l1+1,r1});
            v++;
        }
    }
    while(r1>r2){
        removeVal(arr[--r1]);
        while(v<=c2 && isMedian(v)){
            out.pb({v,l1+1,r1});
            v++;
        }
    }
    cout<<sz(out)<<"\n";
    for(auto &t:out){
        cout<<t[0]<<" "<<t[1]<<" "<<t[2]<<"\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}