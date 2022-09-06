#include <bits/stdc++.h>
using namespace std;
int main() {
    unsigned x = 255;
    unsigned char maska = 1;
    x = x & (~(maska << 4));
    // maska = 00000001
    // maska << 4 = 00010000
    //~() = 11101111
    //128 + 64 + 32 
    cout << x;
    system("pause");
}