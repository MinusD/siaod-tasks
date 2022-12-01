/*
 * Кодирование информации методом Шеннона Фано
 *
 * Входные данные: строка, состоящая из символов латинского алфавита
 *
 * Выходные данные: кодовая таблица, закодированная строка
 *
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
            codes[left] += "0";
            codes[right] += "1";
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
        // Добавление 0 и 1 к кодам
        for (int i = left; i <= right; i++) {
            if  (i <= border - 1) {
                codes[i] += "0";
            } else {
                codes[i] += "1";
            }
        }
        getCodes(left, border - 1);
        getCodes(border, right);
    }

    int getIndex(char c) {
        /*
         * Получение индекса символа
         */
        for (int i = 0; i < symbols.size(); i++) {
            if (symbols[i] == c) {
                return i;
            }
        }
        return -1;
    }

    string code() {
        /*
         * Кодирование
         */
        getFrequency();
        codes.resize(frequencies.size());
        getCodes(0, frequencies.size() - 1);

        string result;
        for (char c : text) {
            result += codes[getIndex(c)];
        }
        return result;
//        return "";
    }

    string decode(string code) {
        /*
         * Декодирование
         */
        string result;
        int i = 0;
        while (i < code.size()) {
            for (int j = 0; j < codes.size(); j++) {
                if (code.substr(i, codes[j].size()) == codes[j]) {
                    result += symbols[j];
                    i += codes[j].size();
                    break;
                }
            }
        }
        return result;
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
                if (frequencies[i] > frequencies[j]) {
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
        for (int i = symbols.size() - 1; i >= 0; i--) {
            cout << symbols[i] << "\t" << codes[i] << endl;
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
    string code = coder.code();
    cout << "Закодированный текст: " << code << endl;
    cout << "Длина закодированного текста: " << code.length() << endl;
    coder.printFrequency();
    coder.printCodes();
    cout << "Декодированный текст: " << coder.decode(code) << endl;
    return 0;
}