#include<bits/stdc++.h>
using namespace std;
void create_file() {
    int n;
    cout << "Amount of numbers: ";
    cin >> n;

    ofstream out;
    out.open("input.txt");

    auto rng = std::default_random_engine {}; //способ генерации случайного числа
    vector<int> nums = vector<int>(n);
    iota(nums.begin(), nums.end(), 0); //range() только на С++
    shuffle(nums.begin(), nums.end(), rng); //перетасуем массив

    for(int i = 0; i < n; i++) {
        out.width(log10(n) + 1); //ширина вывода - число знаков в самом большом числе
        out << nums[i] << " ";
        if (!(i % 10)) out << "\n";
    }
    out.close();
}

int main() {
    create_file();

    auto start_time = chrono::steady_clock::now(); 

    ifstream in;
    in.open("input.txt");

    const int kshift = 7;
    unsigned char block = 0;
    int num = 0;
    vector<unsigned char> mask = vector<unsigned char>(0);

    while(in >> num) {
        int block_n = num / 8;
        int sz = mask.size() - 1;
        if (block_n > sz) {
            for(int j = 0; j < block_n - sz; j++) mask.push_back(block);
        }
        mask[block_n] = mask[block_n] | 1 << (kshift - num % 8);
    }
    in.close();

    ofstream out;
    out.open("output.txt");

    int len = mask.size() * 8;
    for(int i = 0; i < len; i++) {
        out.width(log10(len) + 1);  
        if ((mask[i / 8] >> (kshift - i % 8)) & 1) out << i << " ";
        if(!(i % 20) && i) out << "\n";
    }
    out.close();

    auto end_time = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono:: milliseconds>(end_time - start_time);
    int kbits = (mask.size() * sizeof(unsigned char)) / 1024;

    cout << "Time spent: " << time.count() << "ms" << "\n";
    cout << "Array takes up " << kbits << " kb of RAM" << "\n";

    system("pause");
}