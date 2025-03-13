#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 0;
    cin >> n;

    vector <int> odd;
    vector <int> arr;
    vector <int> even;

    for(int i = 1; i <= n; i++){
        arr.push_back(i);
    }

    for(int i = 0; i < arr.size(); i++){
        if(arr[i] % 2 == 0){
            even.push_back(arr[i]);
        }
        else{
            odd.push_back(arr[i]);
        }
    }
    arr.clear();
    

    for(int i = 0; i < even.size(); i++){
        arr.push_back(even[i]);
    }

    for(int i = 0; i < odd.size(); i++){
        arr.push_back(odd[i]);
    }

    if(n < 4 && n != 1){
        cout << "NO SOLUTION" << endl;
    }
    else{
        for(int i = 0; i < arr.size(); i++){
            cout << arr[i] << " ";
        }
    }
    
}
