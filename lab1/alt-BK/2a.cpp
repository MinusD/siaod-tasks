#include<bits/stdc++.h>
using namespace std;
int main() {

    const int kBitGrid = 8;
    int shift = kBitGrid - 1;
    unsigned char mask = 0;
    int n = 0;

    cin >> n;
    vector<int>nums = vector<int>(n, 0);

    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        // битовый массив имеет следующий вид
        // 0 1 0 0 1 0 1 1
        // 0 1 2 3 4 5 6 7
        mask = mask | 1 << shift - nums[i]; 
    }

    for(int i = 1; i < kBitGrid; i++)
        if (mask >> (shift - i) & 1) cout << i << " ";
    system("pause");
}