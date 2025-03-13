#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 0;
    cin >> n;

    int arr[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    long long counter = 0;

    for (int i = 1; i < n; i++){
        if (arr[i] < arr[i-1]){
           counter += arr[i-1] - arr[i];
           arr[i] = arr[i-1];
        }
    }
    cout << counter;
}
