#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        int n, x;
        cin >> n >> x;
        vector<int> skills(n);
        for (int i = 0; i < n; i++){
            cin >> skills[i];
        }
        
      
        sort(skills.rbegin(), skills.rend());
        
        int currentTeamSize = 0, teamCount = 0;
        for (int i = 0; i < n; i++){
            currentTeamSize++;  
            if ((long long)skills[i] * currentTeamSize >= x) {
                teamCount++;
                currentTeamSize = 0; 
            }
        }
        cout << teamCount << "\n";
    }
    return 0;
}
