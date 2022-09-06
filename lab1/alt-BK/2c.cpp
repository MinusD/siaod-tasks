#include<bits/stdc++.h>
using namespace std;

int main() {
    const int kshift = 7;
    unsigned char block = 0;
    int n = 0;
    
    cin >> n;
    vector<int> nums = vector<int>(n, 0);
    vector<unsigned char> mask = vector<unsigned char>(0);

    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        int block_n = nums[i] / 8; //номер блока, в который попадет число
        int sz = mask.size() - 1;
        if (block_n > sz) {
            for(int j = 0; j < block_n - sz; j++) mask.push_back(block); //добавили необходимое количество новых блоков
        }
        mask[block_n] = mask[block_n] | 1 << (kshift - nums[i] % 8); //обновили маску в блоке по анлалогиии с предыдущим заданием
    }

    //процесс вывода аналогичен
    for(int i = 0; i < mask.size() * 8; i++) {  
        if ((mask[i / 8] >> (kshift - i % 8)) & 1) cout << i << " ";
    }
    system("pause");
}