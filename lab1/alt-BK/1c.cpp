#include<bits/stdc++.h>
using namespace std;
int main() {
    unsigned int x = 25; 
    const int n = sizeof(int)*8; // получили 32 нуля подряд
    unsigned maska = (1 << n - 1); // получили 1 и 31 ноль
    cout << "Mask: " << bitset<n>(maska) << endl; // вывели
    cout << "Result: ";
    for(int i = 1; i <= n; i++) {
        cout << ((x & maska) >> (n - i)); //выводим i-тый старший бит числа
        maska = maska >> 1; //уменьшаем длину маски
    }
    cout << endl;
    system("pause");
}