/*
 * Кодирование информации методом Шеннона Фано
 *
 * Входные данные: строка, состоящая из символов латинского алфавита
 *
 * Выходные данные: кодовая таблица, закодированная строка
 *
 *
<>:0.076923   | 000
r: 0.076923   | 101
o: 0.15385    | 110
H: 0.076923   | 010
l: 0.23077    | 111
w: 0.076923   | 100
d: 0.076923   | 0110
,: 0.076923   | 0011
!: 0.076923   | 0010
e: 0.076923   | 0111

l = 0 d = 6 r = 9
l = 0 d = 3 r = 5
l = 0 d = 1 r = 2
l = 3 d = 4 r = 5
l = 6 d = 8 r = 9
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

class Coder {
    string text;
    int length;
    vector<char> symbols; // Символы
    vector<int> frequencies; // Частоты
    vector<string> codes; // Коды

public:
    explicit Coder(string text) : text(text), length(text.size()) {
        /*
         * Конструктор
         */
    }

    void getCodes(int left, int right) {
        /*
         * Рекурсивная функция для получения кодов
         */
        if (left + 1 == right) {
            codes[frequencies[left]] += '0';
            codes[frequencies[right]] += '1';
            return;
        }

        if (left == right) {
            return;
        }


        int leftSum = 0;
        int rightSum = frequencies[right];
        int border = right;

        // Сумма частот слева от границы
        for (int i = left; i < right; i++) {
            leftSum += frequencies[i];
        }



        // Поиск границы
        while (rightSum < leftSum) {
            border--;
            rightSum += frequencies[border];
            leftSum -= frequencies[border];
        }
        cout << "l = " << left << " d = " << border << " r = " << right << " leftSum: " << leftSum << "rightSum: " << rightSum << endl;
//        cout << "left: " << left << " right: " << right << " border: " << border << endl;

        // Добавление 0 и 1 к кодам
        for (int i = left; i <= right; i++) {
            if (i <= border - 1){
                codes[frequencies[i]] += '0';
            } else {
                codes[frequencies[i]] += '1';
            }
        }

        getCodes(left, border - 1);
        getCodes(border, right);


    }

    string code() {
        /*
         * Кодирование
         */
        getFrequency();
        codes.resize(frequencies.size());
        getCodes(0, frequencies.size() - 1);
        return "";
    }

    void getFrequency() {
        /*
         * Подсчет частоты встречаемости символов
         */
        for (auto ch: text) {
            auto it = find(symbols.begin(), symbols.end(), ch);
            if (it == symbols.end()) {
                symbols.push_back(ch);
                frequencies.push_back(1);
            } else {
                frequencies[it - symbols.begin()]++;
            }
        }

        // Сортируем
        for (int i = 0; i < symbols.size(); i++) {
            for (int j = i + 1; j < symbols.size(); j++) {
                if (frequencies[i] < frequencies[j]) {
                    swap(frequencies[i], frequencies[j]);
                    swap(symbols[i], symbols[j]);
                }
            }
        }
    }

    void printFrequency() {
        cout << "Таблица вероятностей:" << endl;
        cout << "Символ\tЧастота" << endl;
        for (int i = 0; i < symbols.size(); i++) {
            cout << symbols[i] << "\t" << (double)frequencies[i] / length  << endl;
        }
    }

    void printCodes() {
        cout << "Таблица кодов:" << endl;
        cout << "Символ\tКод" << endl;
        for (int i = 0; i < symbols.size(); i++) {
            cout << symbols[i] << "\t" << codes[frequencies[i]] << endl;
        }
    }

};

int main() {
    setlocale(0, "");
    string text;
    cout << "Введите текст: ";
//    getline(cin, text);
    text = "Hello, world!";
    cout << "Исходный текст: " << text << endl;
    cout << "Длина текста: " << text.length() << endl;

    Coder coder(text);
    coder.code();
    coder.printFrequency();
    coder.printCodes();
    return 0;
}