#include <bits/stdc++.h>
using namespace std;
 
static const int MAXN = 10000000;  
static bool isPrime[MAXN+1];
static int piArray[MAXN+1];
 
 
void Pi() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = false;
    isPrime[1] = false;
    for(int i = 2; i * i <= MAXN; i++){
        if(isPrime[i]){
            for(int j = i*i; j <= MAXN; j += i){
                isPrime[j] = false;
            }
        }
    }
    int countPr = 0;
    for(int x = 0; x <= MAXN; x++){
        if(isPrime[x]) countPr++;
        piArray[x] = countPr;
    }
}
 
 
inline int piFunc(int x){
    if(x <= 1) return 0;
    return piArray[x];
}
 
 
long long sumPrimeFloor(long long n){
    if(n < 2) return 0;  
    long long ans = 0;
    long long i = 2;
    while(i <= n){
        long long v = n / i;        
        long long i2 = n / v;      
        if(i2 > n) i2 = n;         
       
        long long cnt = (long long)piFunc((int)i2) - (long long)piFunc((int)(i-1));
        ans += v * cnt;
        i = i2 + 1;
    }
    return ans;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Pi();
    int t;
    cin >> t;
    while(t--){
        long long n;
        cin >> n;
        long long answer = sumPrimeFloor(n);
        cout << answer << "\n";
    }
    return 0;
}