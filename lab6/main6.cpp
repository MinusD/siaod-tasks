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

class HuffmanZipper {
public:
    //сжатие текста
    string zip(string text) {
        text_length = text.size();
        get_frequency(text);
        get_codes();
        string zipped_text = "";
        for (auto ch: text) { //обошли все символы
            //сопоставили им сформированные коды
            zipped_text += code_table[ch].second;
        }

        zip_length = zipped_text.size(); //сохраним длину сжатого текста
        dis_info();
        return zipped_text;
    }

    //восстновление текста
    string unzip(string text) {
        string unzipped_text = "";
        while (text.size() > 0) { //пока остались необработанные символы
            for (auto ch: code_table) { //обходим таблицу кодов
                if (text.find(ch.second.second) == 0) { //если какой-то код совпал с началом строки
                    unzipped_text += ch.first; //добавили символ в ответ
                    text = text.substr(ch.second.second.size(), text.size()); //убрали совпавший фрагмент
                    break; //начали заново
                }
            }
        }
        return unzipped_text;
    }

    //информация о степени сжатия текста
    void dis_info() {
        cout << "The length of the source text: " << text_length * 8 << "\n";
        cout << "Length of compressed text: " << zip_length << "\n";
        cout << "Compression ratio: " << setprecision(5) << (double) text_length * 8 / zip_length << "\n";
    }

    //вывод таблицы символов
    void dis_freq_codes() {
        if (code_table.size() == 0) {
            cout << "No symbols" << "\n";
            return;
        }
        vector<pair<char, pair<int, string>>> info;
        for (auto ch: code_table) info.push_back(ch);
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
            cout << left << setw(10) << setprecision(5) << (double) dt.second.first / text_length << " | ";
            cout << dt.second.second << "\n"; //вывели его код
        }
    }

private:
    //получение таблицы частот
    void get_frequency(string text) {
        set<char> alphabet(text.begin(), text.end());
        for (char ch: alphabet) {
            int cnt = count(text.begin(), text.end(), ch);
            nodes.push_back(new Node(string(1, ch), cnt));
            code_table[ch] = make_pair(cnt, "");
        }
        sort(nodes.begin(), nodes.end(),
             [](const Node *n1, const Node *n2) { return n1->frequency > n2->frequency; });
    }

    //получение таблицы кодов
    void get_codes() {
        while (nodes.size() > 1) {
            Node *l = get_elem();
            Node *r = get_elem();
            Node *parent = new Node(l->symb + r->symb, l->frequency + r->frequency);
            parent->left = l;
            parent->right = r;
            nodes.push_back(parent);
            sort(nodes.begin(), nodes.end(),
                 [](const Node *n1, const Node *n2) { return n1->frequency > n2->frequency; });
        }
        root = get_elem();
        dfs(root, "");
    }

    //вспомогательный метод для обхода графа
    void dfs(Node *root, string code) {
        if (root->left == nullptr || root->right == nullptr) {
            code_table[root->symb[0]].second = code;
            return;
        }
        dfs(root->left, code + "0");
        dfs(root->right, code + "1");
        return;
    }

    //вспомогательный метод для извлечения узла дерева
    Node *get_elem() {
        Node *el = nodes.back();
        nodes.pop_back();
        return el;
    }

    Node *root; //корень H-дерева
    map<char, pair<int, string>> code_table; //таблица кодировки символов
    vector<Node *> nodes; //листья H-дерева
    int text_length = 0; //длина исходного текста
    int zip_length = 0; //длина сжатого текста
};


int main() {
    string s = "Boronin Nikolai Aleksandrovich";
    HuffmanZipper zip;
    string res = zip.zip(s);
    zip.dis_freq_codes();
    cout << res << "\n";
    cout << zip.unzip(res) << "\n";
}