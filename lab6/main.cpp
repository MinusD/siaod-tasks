/*
 * Алогроритм Шеннона-Фано для кодирования и декодирования с выводом в табличном виде
 */

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    /*
     * Структура, описывающая вершину дерева
     */
    char symbol;
    int frequency;
    Node *left;
    Node *right;
};

class Tree {
    /*
     * Класс, описывающий дерево
     */
    Node *root;

    void printTree(Node *node, int level) {
        /*
         * Вспомогательная функция для вывода дерева
         */
        if (node != nullptr) {
            printTree(node->right, level + 1);
            for (int i = 0; i < level; i++) {
                cout << "    ";
            }
            cout << node->symbol << " " << node->frequency << endl;
            printTree(node->left, level + 1);
        }
    }

    void printCode(Node *node, string code) {
        /*
         * Вспомогательная функция для вывода кода
         */
        if (node != nullptr) {
            if (node->left == nullptr && node->right == nullptr) {
                cout << node->symbol << " " << code << endl;
            }
            printCode(node->left, code + "0");
            printCode(node->right, code + "1");
        }
    }

    void deleteTree(Node *node) {
        /*
         * Вспомогательная функция для удаления дерева
         */
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    Tree() {
        /*
         * Конструктор класса
         */
        root = nullptr;
    }

    ~Tree() {
        /*
         * Деструктор класса
         */
        deleteTree(root);
    }

    void addNode(char symbol, int frequency) {
        /*
         * Добавление вершины в дерево
         */
        Node *node = new Node;
        node->symbol = symbol;
        node->frequency = frequency;
        node->left = nullptr;
        node->right = nullptr;
        if (root == nullptr) {
            root = node;
        } else {
            Node *current = root;
            while (true) {
                if (node->frequency < current->frequency) {
                    if (current->left == nullptr) {
                        current->left = node;
                        break;
                    } else {
                        current = current->left;
                    }
                } else {
                    if (current->right == nullptr) {
                        current->right = node;
                        break;
                    } else {
                        current = current->right;
                    }
                }
            }
        }
    }

    void printTree() {
        /*
         * Вывод дерева
         */
        printTree(root, 0);
    }

    void printCode() {
        /*
         * Вывод кода
         */
        printCode(root, "");
    }
};

int main() {
    /*
     * Главная функция
     */
    Tree tree;
    vector<char> symbols;
    vector<int> frequencies;
    int n; // Количество символов
    cin >> n;
    for (int i = 0; i < n; i++) {
        char symbol;
        int frequency;
        cin >> symbol >> frequency;
        symbols.push_back(symbol);
        frequencies.push_back(frequency);
    }
    for (int i = 0; i < n; i++) {
        tree.addNode(symbols[i], frequencies[i]);
    }
    tree.printTree();
    tree.printCode();
    return 0;
}