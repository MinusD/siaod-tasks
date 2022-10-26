/*
 *  Составить программу создания двоичного дерева поиска и реализовать
 *  процедуры для работы с деревом согласно варианту.
 *  Процедуры оформить в виде самостоятельных режимов работы созданного
 *  дерева. Выбор режимов производить с помощью пользовательского
 *  (иерархического ниспадающего) меню.
 *  Провести полное тестирование программы на дереве размером n=10
 *  элементов, сформированном вводом с клавиатуры. Тест-примеры определить
 *  самостоятельно. Результаты тестирования в виде скриншотов экранов
 *  включить в отчет по выполненной работе.
 *  Сделать выводы о проделанной работе, основанные на полученных
 *  результатах.
 *  Оформить отчет с подробным описанием созданного дерева, принципов
 *  программной реализации алгоритмов работы с деревом, описанием текста
 *  исходного кода и проведенного тестирования программы.
 *
 *  Вариант 23
 *  Тип значения узла - Вещественное число.
 *  Тип дерева - Красно-черное дерево.
 *  Процедуры:
 *      1. Вставка узла в дерево и балансировка
 *      2. Прямой обход дерева
 *      3. Симметричный обход дерева
 *      4. Найти сумму значений листьев дерева
 *      5. Найти среднее арифметическое значений всех узлов
 *
 *
 *  Правила:
 *      1. Корень дерева всегда черный.
 *      2. Все листья дерева (NIL) черные.
 *      3. Если узел красный, то оба его потомка черные.
 *      4. Глубина в черных узлах одинакова.
 *
 *
 *
 */

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    double value; // Node value
    Node *left, *right, *parent; // Left, right and parent nodes
    bool color; // false - black, true - red
};

class Tree {
    Node *root;
    Node *nil;

public:
    Tree() {
        /*
         * Constructor for Tree class
         */
        nil = new Node;
        nil->color = false;
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;
        root = nil;
    }

    void add(double value) {
        /*
         * Add new node to tree
         */
        Node *newNode = new Node;
        newNode->value = value;
        newNode->left = nil;
        newNode->right = nil;
        newNode->color = true; // Red

        /*
         * Find place for new node
         */

        Node *current = root;
        Node *parent = nil;

        while (current != nil) {
            parent = current;
            if (newNode->value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        newNode->parent = parent;
        if (parent == nil) {
            root = newNode;
        } else if (newNode->value < parent->value) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        if (newNode->parent == nil) {
            newNode->color = false;
            return;
        }

        if (newNode->parent->parent == nil) {
            return;
        }



//        while (current != nil) {
//            if (value < current->value) {
//                if (current->left == nil){
//                    current->left = newNode;
//                    newNode->parent = current;
//                    break;
//                } else {
//                    current = current->left;
//                }
//            } else {
//                if (current->right == nil){
//                    current->right = newNode;
//                    newNode->parent = current;
//                    break;
//                } else {
//                    current = current->right;
//                }
//            }
//        }

        if (root == nil) {
            root = newNode;
            root->color = false; // Black
        }

    }

    void showTreeGraphiz(Node *node = nullptr, Node *prev = nullptr, bool isLeft = false) {
        /*
         * Show tree Graphiz
         */
        if (node == nullptr) {
            node = root;
        }
//        cout << node->value << " [color=" << (node->color ? "red" : "black") << "];" << endl;
        if (node != nil) {
            if (node->left != nil) {
                cout << node->value << " [color=" << (node->color ? "red" : "black") << "];" << endl;
                cout << node->value << " -> " << node->left->value << ";" << endl;
            }
            if (node->right != nil) {
                cout << node->value << " [color=" << (node->color ? "red" : "black") << "];" << endl;
                cout << node->value << " -> " << node->right->value << ";" << endl;
            }
            showTreeGraphiz(node->left, node, true);
            showTreeGraphiz(node->right, node, false);
        } else {
            if (prev != nullptr) {
                cout << "\"nil_" << prev->value << (isLeft ? "_l\"" : "_r\"") << " [color=black];" << endl;
                cout << prev->value << " -> " << "\"nil_" << prev->value << (isLeft ? "_l\"" : "_r\"") << endl;
            }
        }


    }
};


int main() {
    Tree tree;
    vector<double> values = {1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3, 8.3, 9.3, 10.3};
    // Перемешать значения
    for (int i = 0; i < values.size(); i++) {
        int index = rand() % values.size();
        double temp = values[i];
        values[i] = values[index];
        values[index] = temp;
    }
    for (double value: values) {
        tree.add(value);
    }
    cout << "digraph G {" << endl;
    tree.showTreeGraphiz();
    cout << "}" << endl;
    return 0;
}
