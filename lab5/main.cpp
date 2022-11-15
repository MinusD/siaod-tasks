/*
 * Составить программу создания графа и реализовать процедуру для работы с
 * графом, определенную индивидуальным вариантом задания.
 *
 * Самостоятельно выбрать и реализовать способ представления графа в памяти.
 * В программе предусмотреть ввод с клавиатуры произвольного графа. В
 * вариантах построения остовного дерева также разработать доступный способ
 * (форму) вывода результирующего дерева на экран монитора.
 *
 *
 * Нахождение кратчайшего пути методом Йена
 */

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Node {
    /*
     * Структура, описывающая вершину графа
     */
    string name;
};

class Graph {
    /*
     * Класс, описывающий граф
     */

    int size; // Количество вершин графа
    vector<vector<int>> matrix; // Матрица смежности
    vector<Node *> nodes; // Список вершин графа

public:
    Graph() {
        /*
         * Конструктор класса
         */
        size = 0;
    }

    void addNode(string name) {
        /*
         * Добавление вершины в граф
         */
        Node *node = new Node;
        node->name = std::move(name);
        nodes.push_back(node);
        size++;
        matrix.resize(size);
        for (int i = 0; i < size; i++) {
            matrix[i].resize(size);
        }
    }

    void addEdge(string name1, string name2, int distance) {
        /*
         * Добавление ребра в граф
         */
        int index1 = -1;
        int index2 = -1;
        for (int i = 0; i < size; i++) {
            if (nodes[i]->name == name1) {
                index1 = i;
            }
            if (nodes[i]->name == name2) {
                index2 = i;
            }
        }
        if (index1 == -1 || index2 == -1) {
            cout << "Error: node not found" << endl;
            return;
        }
        matrix[index1][index2] = distance;
        matrix[index2][index1] = distance;
    }

    Node *getNode(string name) {
        /*
         * Получение вершины по имени
         */
        for (int i = 0; i < size; i++) {
            if (nodes[i]->name == name) {
                return nodes[i];
            }
        }
        return nullptr;
    }

    int getIndex(string name) {
        /*
         * Получение индекса вершины по имени
         */
        for (int i = 0; i < size; i++) {
            if (nodes[i]->name == name) {
                return i;
            }
        }
        return -1;
    }

    void print() {
        /*
         * Вывод графа на экран
         */

        vector<string> printedTo;
        vector<string> printedFrom;
        cout << "digraph G {" << endl;
        for (int i = 0; i < size; i++) {
            for (int j = i; j < size; j++) {
                if (matrix[i][j] != 0) {
                    string from = nodes[i]->name;
                    string to = nodes[j]->name;

                    if (find(printedTo.begin(), printedTo.end(), to) == printedTo.end() ||
                        find(printedFrom.begin(), printedFrom.end(), from) == printedFrom.end()) {
                        cout << "    " << from << " -> " << to << " [label=\"" << matrix[i][j] << "\", arrowhead=none];" << endl;
                        printedTo.push_back(to);
                        printedFrom.push_back(from);
                    }
                }
            }
        }
        cout << "}" << endl;
    }

    int searchRoute(string name, string name2) {
        /*
         * Поиск кратчайшего пути между двумя вершинами
         */

        int index = getIndex(name); // Индекс начальной вершины
        int index2 = getIndex(name2); // Индекс конечной вершины
        if (index == -1 || index2 == -1) { // Если вершины не найдены
            cout << "Error: node not found" << endl;
            return -1;
        }

        // Массив, содержащий расстояния от начальной вершины до всех остальных
        vector<int> distances(size, -1);

        // Массив, содержащий индексы вершин, которые уже были просмотрены
        vector<int> visited(size, 0);
        distances[index] = 0;
        visited[index] = 1;
        int current = index; // Начинаем с начальной вершины

        // Пока не просмотрены все вершины
        while (current != index2) {

            // Просматриваем все ребра, исходящие из текущей вершины
            for (int i = 0; i < size; i++) {

                // Если ребро существует и вершина еще не была просмотрена
                if (matrix[current][i] != 0 && visited[i] == 0) {

                    // Если расстояние до вершины еще не было вычислено, либо вычисленное расстояние больше, чем расстояние через текущую вершину
                    if (distances[i] == -1 || distances[i] > distances[current] + matrix[current][i]) {

                        // Обновляем расстояние до вершины
                        distances[i] = distances[current] + matrix[current][i];
                    }
                }
            }

            // Ищем вершину с минимальным расстоянием
            int min = -1;

            // Просматриваем все вершины
            for (int i = 0; i < size; i++) {

                // Если вершина еще не была просмотрена и расстояние до нее было вычислено
                if (visited[i] == 0 && distances[i] != -1) {

                    // Если минимальное расстояние еще не было вычислено, либо вычисленное минимальное расстояние больше, чем расстояние до текущей вершины
                    if (min == -1 || distances[i] < distances[min]) {
                        min = i;
                    }
                }
            }

            // Если минимальное расстояние не было вычислено, значит путь не существует
            if (min == -1) {
                break;
            }
            current = min;

            // Помечаем вершину как просмотренную
            visited[current] = 1;
        }

        return distances[index2];
    }

};

int main() {
    Graph graph;
    graph.addNode("L");
    graph.addNode("B");
    graph.addNode("A");
    graph.addNode("N");
    graph.addNode("M");
    graph.addNode("G");
    graph.addNode("S");
    graph.addNode("R");
    graph.addNode("D");

    graph.addEdge("L", "B", 7);
    graph.addEdge("B", "A", 27);
    graph.addEdge("L", "N", 10);
    graph.addEdge("B", "G", 9);
    graph.addEdge("G", "S", 11);
    graph.addEdge("A", "M", 15);
    graph.addEdge("N", "G", 8);
    graph.addEdge("N", "R", 31);
    graph.addEdge("R", "D", 32);
    graph.addEdge("S", "D", 17);
    graph.addEdge("S", "M", 15);
    graph.addEdge("D", "M", 21);

    graph.print();

    cout << "Distance L - R: " << graph.searchRoute("L", "D") << endl;
    cout << "Distance R - M: " << graph.searchRoute("R", "M") << endl;
    return 0;
}