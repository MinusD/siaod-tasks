#include <iostream>
#include <bitset>

using namespace std;

void task1a();
void task1b();
void task1c();
void task2a();

int main()
{
    setlocale(0, "");

    task1a();
    task1b();
    task1c();

    task2a();
}


void task1a() {
    cout << "Task 1.a\n";
    unsigned char x = 255; // 255 16 (00010000)
    unsigned char mask = 1;
    x = x & (~(mask << 4));
    cout << bitset<8>(x);
}

void task1b() {
    cout << "\n\nTask 1.б\n";
    unsigned char x = 0;
    unsigned char mask = 1;
    x = x | (mask << 6);
    cout << bitset<8>(x);
}

void task1c() {
    cout << "\n\nTask 3.в\n";
    unsigned int a = 25;
    const int n = sizeof(int) * 8;
    unsigned maska = (1 << n - 1); // Помещаем 1 в старший разряд
    cout << "Start mask: " << bitset<n>(maska) << endl;
    cout << "Result: ";
    for (int i = 1; i <= n; i++) {
        cout << ((a & maska) >> (n - i));
        maska >>= 1;
    }
}

void task2a() {

}