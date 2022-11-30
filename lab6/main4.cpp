/*
 * Кодирование информации методом Шеннона Фано
 *
 * Входные данные: строка, состоящая из символов латинского алфавита
 *
 * Выходные данные: кодовая таблица, закодированная строка
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <numeric>

using namespace std;

class ShannonZipper {
public:
    //формирование сжатого текста
    string zip(string text) {

        text_length = text.size(); //cохрнили длину сжимаемого текста
        //получили таблицу частот и кодов
        get_frequency(text);
        get_codes(0, frequencies.size() - 1);

        string zipped_text = "";
        for (auto ch: text) { //обошли все символы
            //сопоставили им сформированные коды
            zipped_text += code_table[ch];
        }

        zip_length = zipped_text.size(); //сохраним длину сжатого текста
        dis_info();
        return zipped_text;
    }

    //формирование восстановленного текста
    string unzip(string text) {
        string unzipped_text = "";
        while (text.size() > 0) { //пока остались необработанные символы
            for (auto ch: code_table) { //обходим таблицу кодов
                if (text.find(ch.second) == 0) { //если какой-то код совпал с началом строки
                    unzipped_text += ch.first; //добавили символ в ответ
                    text = text.substr(ch.second.size(), text.size()); //убрали совпавший фрагмент
                    break; //начали заново
                }
            }
        }
        return unzipped_text;
    }

    //вывод таблицы символов
    void dis_freq_codes() {
        if (code_table.size() == 0) {
            cout << "No symbols" << "\n";
            return;
        }
        //поиск минимального элемента в map, возвращает pair<char, int>
        // auto ch = min_element(frequencies.begin(), frequencies.end(),
        // [](const auto &l, const auto &r) {return l.second < r.second; });
        vector<pair<char, string>> info;
        for (auto pair: code_table) info.push_back(pair);
        sort(info.begin(), info.end(),
             [](std::pair<char, string> s1, std::pair<char, string> s2) {
                 return s1.second.size() < s2.second.size();
             });
        for (auto pair: info) {
            char ch = pair.first;
            if (ch == '\n') cout << "/n:";
            else if (ch == ' ') cout << "<>:";
            else cout << ch << left << setw(2) << ":"; //вывели символ
            //указали его частоту
            auto it = find_if(frequencies.begin(), frequencies.end(),
                              [ch](std::pair<char, int> &el) { return el.first == ch; });

            cout << left << setw(10) << setprecision(5) << (double) it->second / text_length << " | ";
            cout << pair.second << "\n"; //вывели его код
        }
    }

    //информация о степени сжатия текста
    void dis_info() {
        cout << "The length of the source text: " << text_length * 8 << "\n";
        cout << "Length of compressed text: " << zip_length << "\n";
        cout << "Compression ratio: " << setprecision(5) << (double) text_length * 8 / zip_length << "\n";
    }

private:
    //формирование таблицы частот
    void get_frequency(string text) {
        set<char> alphabet(text.begin(), text.end());
        for (auto ch: alphabet) {
            int cnt = count(text.begin(), text.end(), ch);
            frequencies.push_back(make_pair(ch, cnt));
        }
        sort(frequencies.begin(), frequencies.end(),
             [](const std::pair<char, int> &s1, const std::pair<char, int> &s2) { return s1.second < s2.second; });
    }

    //формирование кодов для всех символов алфавита
    void get_codes(int l, int r) {
        // l - левая граница текущего рассматрвиаемого массива
        // r - правая граница текущего рассматрвиаемого массива
        //если l + 1 = r - значит текущий массив при разбиении даст два элемента, верхний - 1, нижний - 0
        if (l + 1 == r) {
            code_table[frequencies[l].first] += "0";
            code_table[frequencies[r].first] += "1";
            return;
        }

        if (l == r) return; //одному символу бит уже был проставлен уровнем выше

        //посчитаем сумму всех элементов, кроме последнего
        //пока она больше, будем cдвигать границу влево
        int d = r;
        int sum_l = 0; //сумма левой части массива
        int sum_r = frequencies[r].second; //сумма правой части массива

        auto accumulate_fun = [](int accumulator, const std::pair<char, int> &s1) { return accumulator + s1.second; };
        sum_l = accumulate(frequencies.begin() + l, frequencies.begin() + r, 0, accumulate_fun);
        while (sum_r < sum_l) { //добиваемся примерного равенства частей
            d--;
            sum_r += frequencies[d].second;
            sum_l -= frequencies[d].second;
        }

        //получили два массива: [l, d-1] и [d, r]
        //проставим им соответсвующие биты
        cout << "l = " << l << " d = " << d << " r = " << r << "\n";
        for (int i = l; i <= r; i++) {
            if (i <= d - 1) code_table[frequencies[i].first] += "0";
            else code_table[frequencies[i].first] += "1";
        }

        //продолжаем делить имеющиеся два массива
        get_codes(l, d - 1);
        get_codes(d, r);
    }

    map<char, string> code_table; //таблица кодов символов
    vector<pair<char, int>> frequencies; //таблица частот символов
    int text_length = 0; //длина исходного текста
    int zip_length = 0; //длина сжатого текста
};


int main() {

    ShannonZipper zip;
    string text = "Hello, world!";

    string res = zip.zip(text);
    cout << "\n";
    cout << "Zip res:" << res << "\n\n";
    zip.dis_freq_codes();
    cout << "Unzip res: " << "\n";
    cout << zip.unzip(res) << "\n";
}