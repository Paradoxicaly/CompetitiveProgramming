#include <iostream>
#include <vector>
using namespace std;
 
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> count(10, 0);
        int answer = 0;
        for (int i = 1; i <= n; i++){
            int digit;
            cin >> digit;
            count[digit]++;
            if(count[0] >= 3 && count[1] >= 1 && count[2] >= 2 
               && count[3] >= 1 && count[5] >= 1 && answer == 0) {
                answer = i;
            }
        }
        cout << answer << "\n";
    }
    return 0;
}
