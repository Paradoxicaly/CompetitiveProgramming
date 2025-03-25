#include <bits/stdc++.h>
using namespace std;
 
long long rowCap(long long m, long long L) {
    long long b = (m + 1) / (L + 1);  
    long long r = (m + 1) - b * (L + 1);
    long long result = b * L;
    long long leftoverBench = max(0LL, r - 1);
    result += min(L, leftoverBench);
    return result;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        long long n, m, k;
        cin >> n >> m >> k;
 
        if(k == n * m){
            cout << m << "\n";
            continue;
        }
        long long low = 1, high = min(k, m);
        while(low < high){
            long long mid = (low + high) / 2;
            long long canSeat = rowCap(m, mid);
            long long total = canSeat * n;
            
            if(total >= k){
                
                high = mid;
            } else {
              
                low = mid + 1;
            }
        }
        
 
        cout << low << "\n";
    }
    return 0;
}