#include <bits/stdc++.h>
using namespace std;

int main() {
	long long int n = 0;
    long long int squared = 0;
    long long int diff = 0;
    cin >> n;

    vector<pair<int, int>> pairs;  

    for (long long int i = 0; i < n; i++) {
        long long int y, x;
        cin >> y >> x;  
        pairs.push_back({y, x});
    }
    

    for(long long int i = 0; i < pairs.size(); i++){
        long long int first = pairs[i].first;
        long long int second = pairs[i].second;
        squared = (max(first, second) * max(first,second)) - (max(first,second)-1);
        

        if(first == second){
            cout << squared << endl;
        }
        else if(first > second && first % 2 == 0){
            diff = first - second;
            cout << squared + diff << endl;
        }
        else if(first > second && first % 2 == 1){
            diff = first - second;
            cout << squared - diff << endl;
        }
        else if(first < second && second % 2 == 0){
            diff = second - first;
            cout << squared - diff << endl;
        }
        else if(first < second && second % 2 == 1){
            diff = second - first;
            cout << squared + diff << endl;
        }
        
    }
}