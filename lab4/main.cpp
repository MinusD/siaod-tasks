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
 *  https://dreampuf.github.io/GraphvizOnline/
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

        fixTree(newNode);

        if (root == nil) {
            root = newNode;
            root->color = false; // Black
        }

    }

    void fixTree(Node *node) {
        /*
         * Fix tree after adding new node
         */
        Node *parent = nil;
        Node *grandparent = nil;

        while ((node != root) && (node->color != false) && (node->parent->color == true)) {
            parent = node->parent;
            grandparent = node->parent->parent;

            if (parent == grandparent->left) {
                Node *uncle = grandparent->right;

                if (uncle->color == true) {
                    grandparent->color = true;
                    parent->color = false;
                    uncle->color = false;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        leftRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rightRotate(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                Node *uncle = grandparent->left;

                if (uncle->color == true) {
                    grandparent->color = true;
                    parent->color = false;
                    uncle->color = false;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        rightRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    leftRotate(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        root->color = false;
    }

    void leftRotate(Node *node) {
        Node *right = node->right;
        node->right = right->left;

        if (node->right != nil) {
            node->right->parent = node;
        }

        right->parent = node->parent;

        if (node->parent == nil) {
            root = right;
        } else if (node == node->parent->left) {
            node->parent->left = right;
        } else {
            node->parent->right = right;
        }

        right->left = node;
        node->parent = right;
    }

    void rightRotate(Node *node) {
        Node *left = node->left;
        node->left = left->right;

        if (node->left != nil) {
            node->left->parent = node;
        }

        left->parent = node->parent;

        if (node->parent == nil) {
            root = left;
        } else if (node == node->parent->left) {
            node->parent->left = left;
        } else {
            node->parent->right = left;
        }

        left->right = node;
        node->parent = left;
    }

    void showGraphiz() {
        cout << "digraph G {" << endl;
        showTreeGraphiz();
        cout << "}" << endl;
    }

    // Прямой обход
    void showTree(Node *node = nullptr) {
        if (node == nullptr) {
            node = root;
        }
        if (node != nil) {
            cout << node->value << " ";
            showTree(node->left);
            showTree(node->right);
        }
    }

    // Симметричный обход
    void showTreeSymmetric(Node *node = nullptr) {
        if (node == nullptr) {
            node = root;
        }
        if (node != nil) {
            showTreeSymmetric(node->left);
            cout << node->value << " ";
            showTreeSymmetric(node->right);
        }
    }

    // Сумма листьев
    double sumLeaves(Node *node = nullptr) {
        if (node == nullptr) {
            node = root;
        }
        if (node != nil) {
            if (node->left == nil && node->right == nil) {
                return node->value;
            }
            return sumLeaves(node->left) + sumLeaves(node->right);
        }
        return 0;
    }

    // Среднее арифметическое всех узлов
    double averageNodes(Node *node = nullptr) {
        if (node == nullptr) {
            node = root;
        }
        if (node != nil) {
            return sumNodes(node) / countNodes(node);
        }
        return 0;
    }

private:
    // Количество узлов
    int countNodes(Node *node = nullptr) {
        if (node == nullptr) {
            node = root;
        }
        if (node != nil) {
            return 1 + countNodes(node->left) + countNodes(node->right);
        }
        return 0;
    }

    // Сумма всех узлов
    double sumNodes(Node *node = nullptr) {
        if (node == nullptr) {
            node = root;
        }
        if (node != nil) {
            return node->value + sumNodes(node->left) + sumNodes(node->right);
        }
        return 0;
    }

    // Вывод дерева в формате Graphiz
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
//            if (prev != nullptr) {
//                cout << "\"nil_" << prev->value << (isLeft ? "_l\"" : "_r\"") << " [color=black];" << endl;
//                cout << prev->value << " -> " << "\"nil_" << prev->value << (isLeft ? "_l\"" : "_r\"") << endl;
//            }
        }


    }

};


int main() {
    system("chcp 65001");

    Tree tree;
    vector<double> values = {
            1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3, 8.3, 9.3, 10.3,
//            11.3, 12.3, 13.3, 14.3, 15.3, 16.3, 17.3, 18.3, 19.3, 20.3,
//            21.3, 22.3, 23.3, 24.3, 25.3, 26.3, 27.3, 28.3, 29.3, 30.3,
//            31.3, 32.3, 33.3, 34.3, 35.3, 36.3, 37.3, 38.3, 39.3, 40.3,
    };
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

    // Текстовое меню
    int choice = 0;
    while (choice != 7) {
        cout << "1. Добавление элемента" << endl;
        cout << "2. Показать дерево (Прямой ход)" << endl;
        cout << "3. Симметричный обход" << endl;
        cout << "4. Сумма листьев" << endl;
        cout << "5. Среднее арифметическое всех узлов" << endl;
        cout << "6. Показать дерево Graphiz" << endl;
        cout << "7. Выход" << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                double value;
                cout << "Введите значение: ";
                cin >> value;
                tree.add(value);
                break;
            }
            case 2: {
                tree.showTree();
                cout << endl;
                break;
            }
            case 3: {
                tree.showTreeSymmetric();
                cout << endl;
                break;
            }
            case 4: {
                cout << "Сумма листьев: " << tree.sumLeaves() << endl;
                break;
            }
            case 5: {
                cout << "Среднее арифметическое всех узлов: " << tree.averageNodes() << endl;
                break;
            }
            case 6: {
                tree.showGraphiz();
                break;
            }
            case 7: {
                break;
            }
            default: {
                cout << "Неверный пункт меню" << endl;
                break;
            }
        }
    }

    return 0;
}
