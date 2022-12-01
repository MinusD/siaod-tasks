/*
 * Кодирование и декодирование Метод Хаффмана
 *
 * Входные данные: текстовый файл
 *
 * Выходные данные: закодированный текстовый файл
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <set>

using namespace std;

struct Node { //узел Н-дерева
    Node(string symbols, int fr) : symb(symbols), frequency(fr) {}

    Node *left = nullptr;
    Node *right = nullptr;
    int frequency = 0;
    string symb = "";
};

class Coder {
    string text;
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
        while (text.size() > 0) { //пока остались необработанные символы
            for (auto ch: codes) { //обходим таблицу кодов
                if (text.find(ch.second.second) == 0) { //если какой-то код совпал с началом строки
                    result += ch.first; //добавили символ в ответ
                    text = text.substr(ch.second.second.size(), text.size()); //убрали совпавший фрагмент
                    break; //начали заново
                }
            }
        }
        return result;
    }


    //вывод таблицы символов
    void dis_freq_codes() {
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
            else if (ch == ' ') cout << "<>:";
            else cout << ch << left << setw(2) << ":"; //вывели символ
            cout << dt.second.first << " |";
            cout << left << setw(10) << setprecision(5) << (double) dt.second.first / length << " | ";
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
        while (nodes.size() > 1) {
            Node *l = getElem();
            Node *r = getElem();
            Node *parent = new Node(l->symb + r->symb, l->frequency + r->frequency);
            parent->left = l;
            parent->right = r;
            nodes.push_back(parent);
            sort(nodes.begin(), nodes.end(),
                 [](const Node *n1, const Node *n2) { return n1->frequency > n2->frequency; });
        }
        root = getElem();
        graph(root, "");
    }

    //вспомогательный метод для обхода графа
    void graph(Node *root, string code) {
        if (root->left == nullptr || root->right == nullptr) {
            codes[root->symb[0]].second = code;
            return;
        }
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

    Node *root; // Корень дерева
    map<char, pair<int, string>> codes; // Таблица кодов
    vector<Node *> nodes; // Вектор узлов
    int length = 0; // Длина текста
    int zip_length = 0; // Длина сжатого текста
};


int main() {
    string s = "Gizatullina Alsu Ilnurovna";
    Coder coder(s);
    string res = coder.code();
    coder.dis_freq_codes();
    cout << res << "\n";
    cout << coder.decode(res) << "\n";
}