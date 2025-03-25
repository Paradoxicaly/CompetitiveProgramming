#include <bits/stdc++.h>
using namespace std;
 
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while(t--){
        long long n;
        cin >> n;
 
      
        if(n == 4) {
           
            cout << -1 << "\n";
            continue;
        }
        if(n == 5) {
            
            cout << "4 1 3 5 2\n";
            continue;
        }
        if(n == 3) {
           
            cout << "1 3 2\n";
            continue;
        }
     
        if(n == 1){
            cout << 1 << "\n";
            continue;
        }
 
       
        if(n % 2 == 0){
            cout << -1 << "\n";
            continue;
        }
 
       
        vector<long long> p(n);
        for(long long i = 1; i <= n; i++){
            long long val = (2LL * i) % n; 
            if(val == 0) val = n;          
            p[i-1] = val;
        }
        for(int i = 0; i < n; i++){
            cout << p[i] << (i + 1 < n ? ' ' : '\n');
        }
    }
    return 0;
}