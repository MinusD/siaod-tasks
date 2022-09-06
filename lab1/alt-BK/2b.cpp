#include<bits/stdc++.h>
using namespace std;
int main() {

    const int kBitGrid = 64;
    int shift = kBitGrid - 1;
    unsigned long long mask = 0;
    int n = 0;

    cin >> n;
    vector<int>nums = vector<int>(n, 0);

    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        mask = mask | 1ull << (shift - nums[i]);
    }

    for(int i = 0; i < kBitGrid; i++)
        if ((mask >> shift - i) & 1) cout << i << " ";
        //if(mask >> i & 1) cout << shift - i << " "; //сортировка по убыванию
    system("pause");
}