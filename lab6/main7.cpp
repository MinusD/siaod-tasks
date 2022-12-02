#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <set>

using namespace std;

struct Node { // Узел дерева
    Node(string symbols, int fr) : symb(symbols), frequency(fr) {}

    Node *left = nullptr;
    Node *right = nullptr;
    int frequency = 0;
    string symb = "";
};

class Coder {
    string text; // Исходный текст
    Node *root; // Корень дерева
    map<char, pair<int, string>> codes; // Таблица кодов
    vector<Node *> nodes; // Вектор узлов
    int length = 0; // Длина текста
    int encodeLength = 0; // Длина сжатого текста
public:

    Coder(string text) : text(text), length(text.size()) {
        /*
         * Конструктор
         */
    }

    //сжатие текста
    string code() {
        getFrequency();
        getCodes();
        string result = "";
        for (auto ch: text) {
            result += codes[ch].second;
        }
        return result;
    }

    string decode(string text) {
        string result = "";
        while (!text.empty()) { // Пока остались необработанные символы
            for (auto ch: codes) { // Обходим таблицу кодов
                if (text.find(ch.second.second) == 0) { // Если какой-то код совпал с началом строки
                    result += ch.first; // Добавляем символ в результат
                    text = text.substr(ch.second.second.size(), text.size()); // Убираем из строки обработанный код
                    break; // Переходим к следующему символу
                }
            }
        }
        return result;
    }


    //вывод таблицы символов
    void showCodes() {
        if (codes.size() == 0) {
            cout << "No symbols" << "\n";
            return;
        }
        vector<pair<char, pair<int, string>>> info;
        for (auto ch: codes) info.push_back(ch);
        sort(info.begin(), info.end(),
             [](pair<char, pair<int, string>> s1, pair<char, pair<int, string>> s2) {
                 return s1.second.second.size() < s2.second.second.size();
             });

        for (auto dt: info) {
            char ch = dt.first;
            if (ch == '\n') cout << "/n:";
            else cout << ch << left << setw(2) << ":"; //вывели символ
            cout << dt.second.first << "\t";
            cout << left << setw(10) << setprecision(5) << (double) dt.second.first / length << " ";
            cout << dt.second.second << "\n"; //вывели его код
        }
    }

    void getFrequency() {
        set<char> chars(text.begin(), text.end());

        // Подсчет частоты символов
        for (char ch: chars) {
            int cnt = count(text.begin(), text.end(), ch);
            nodes.push_back(new Node(string(1, ch), cnt));
            codes[ch] = make_pair(cnt, "");
        }

        // Сортировка по частоте
        sort(nodes.begin(), nodes.end(),
             [](const Node *n1, const Node *n2) { return n1->frequency > n2->frequency; });
    }


    void getCodes() {
        while (nodes.size() > 1) { // Пока в векторе есть хотя бы два элемента
            Node *l = getElem(); // Получаем минимальный элемент
            Node *r = getElem(); // Получаем следующий минимальный элемент
            Node *parent = new Node(l->symb + r->symb, l->frequency + r->frequency); // Создаем новый узел
            parent->left = l; // Устанавливаем левого потомка
            parent->right = r; // Устанавливаем правого потомка
            nodes.push_back(parent); // Добавляем в вектор
            sort(nodes.begin(), nodes.end(), // Сортируем по частоте
                 [](const Node *n1, const Node *n2) { return n1->frequency > n2->frequency; });
        }
        root = getElem(); // Получаем корень дерева
        graph(root, "");
    }

    // Вспомогательный метод для обхода графа
    void graph(Node *root, string code) {
        // Если узел не пустой
        if (root->left == nullptr || root->right == nullptr) {
            // Если узел лист
            codes[root->symb[0]].second = code; // Записываем код
            return;
        }

        // Если узел не лист
        graph(root->left, code + "0");
        graph(root->right, code + "1");
    }

    Node *getElem() {
        /*
         * Извлечение узла дерева
         */
        Node *el = nodes.back();
        nodes.pop_back();
        return el;
    }
};


int main() {
    string s = "gizatullina alsu ilnurovna";
    Coder coder(s);
    string res = coder.code();
    coder.showCodes();
    cout << res << "\n";
    cout << coder.decode(res) << "\n";
    // Коэффициент сжатия
    cout << "Коэффициент сжатия: " << (double) res.size() / (s.size() * 8) << "\n";
}