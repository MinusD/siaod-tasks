#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

void task1a();
void task1b();
void task1c();
void task2a();
void task2b();
void task2c();

int main()
{
    setlocale(0, "");

    task1a();
    task1b();
    task1c();

    task2a();
    task2b();
    task2c();
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
    cout << "\n\nTask 1.в\n";
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
    cout << "\n\nTask 2.а\n";
    unsigned char data = 0;
    short int size, tmp;
    cout << "Enter array size: ";
    cin >> size;
    for (int i = 0; i < size; i++) 
    {
        cin >> tmp;
        data = data | (1 << tmp);
    }

    //cout << bitset<8>(data) << endl;
    cout << "Sorted array: ";
    for (int i = 0; i < sizeof(data) * 8; i++)
    {
        if ((1 << i) & data) cout << i << " ";
    }
}

void task2b() {
    cout << "\n\nTask 2.б\n";
    unsigned long long data = 0, mask = 1;
    short int size, tmp;
    cout << "Enter array size: ";
    cin >> size;
    for (int i = 0; i < size; i++)
    {
        mask = 1;
        cin >> tmp;
        data = data | (mask << tmp);
    }
    cout << "Sorted array: ";
    for (int i = 0; i < sizeof(data) * 8; i++)
    {
        mask = 1;
        if ((mask << i) & data) cout << i << " ";
    }
}


void task2c() {
    cout << "\n\nTask 2.в\n";
    int size, tmp;
    vector<unsigned char> data;
    cout << "Enter array size: ";
    cin >> size;
    for (int i = 0; i < 8; i++)
        data.push_back(0);

    for (int i = 0; i < size; i++) {
        cin >> tmp;
        data[tmp / 8] = data[tmp / 8] | (1 << (tmp % 8));
    }

    cout << "Sorted array: ";
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if ((1 << j) & data[i]) cout << i * 8 + j << " ";
}

