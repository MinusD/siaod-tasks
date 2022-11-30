/*
 * Составление таблицы вероятностей для кодирования Шеннона-Фано
 *
 * Входные данные:
 * 1. Исходный текст
 *
 * Выходные данные:
 * 1. Таблица вероятностей
 */

#include <iostream>
#include <vector>
//#include <windows.h>
#include <string>
using namespace std;


int main(){
    setlocale(0, "");
    system("chcp 65001");
//    SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
//    SetConsoleOutputCP(1251); // Вывод на консоль в кодировке 1251
    string text;
    cout << "Введите текст: ";
    getline(cin, text);
    cout << "Исходный текст: " << text << endl;
    cout << "Длина текста: " << text.length() << endl;

    for (int i = 0; i < text.length(); ++i) {

    }
    vector<string> symbols;
    vector<int> frequencies;
    // Подсчет частоты встречаемости символов
    for (int i = 0; i < text.length(); i++){
        bool found = false;
        for (int j = 0; j < symbols.size(); j++){
            if (symbols[j] == text.substr(i, 1)){
                frequencies[j]++;
                found = true;
                break;
            }
        }
        if (!found){
            symbols.push_back(text.substr(i, 1));
            frequencies.push_back(1);
        }
    }

    cout << "Таблица вероятностей:" << endl;
    cout << "Символ\tЧастота" << endl;
    for (int i = 0; i < symbols.size(); i++){
        cout << symbols[i] << "\t" << frequencies[i] << endl;
    }
    return 0;
}
