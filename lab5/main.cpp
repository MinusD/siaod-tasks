/*
 * Составить программу создания графа и реализовать процедуру для работы с
графом, определенную индивидуальным вариантом задания.

Самостоятельно выбрать и реализовать способ представления графа в памяти.
В программе предусмотреть ввод с клавиатуры произвольного графа. В
вариантах построения остовного дерева также разработать доступный способ
(форму) вывода результирующего дерева на экран монитора.


 * Нахождение кратчайшего пути методом Йена
 */

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    /*
     * Структура, описывающая вершину графа
     */
    string name;
    vector<Node *> neighbours; // Список смежных вершин
    vector<int> distances; // Список расстояний (весов) ребер
};

class Graph {
    /*
     * Класс, описывающий граф
     */
    vector<Node *> nodes; // Список вершин графа
    int size; // Количество вершин графа

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
            node->name = name;
            nodes.push_back(node);
            size++;
        }

        void addEdge(string name1, string name2, int distance) {
            /*
             * Добавление ребра в граф
             */
            Node *node1 = getNode(name1);
            Node *node2 = getNode(name2);
            node1->neighbours.push_back(node2);
            node1->distances.push_back(distance);
            node2->neighbours.push_back(node1);
            node2->distances.push_back(distance);
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

        void print() {
            /*
             * Вывод графа на экран
             */

            vector<string> printedTo;
            vector<string> printedFrom;
            cout << "digraph G {" << endl;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < nodes[i]->neighbours.size(); j++) {
                    bool isPrinted = false;
                    for (int k = 0; k < printedTo.size(); k++) {
                        if (printedFrom[k] == nodes[i]->name && printedTo[k] == nodes[i]->neighbours[j]->name) {
                            isPrinted = true;
                            break;
                        }
                    }
                    if (!isPrinted) {
                        cout << nodes[i]->name << " -> " << nodes[i]->neighbours[j]->name << " [label=\"" << nodes[i]->distances[j] << "\"];" << endl;
                        printedTo.push_back(nodes[i]->name);
                        printedFrom.push_back(nodes[i]->neighbours[j]->name);

                    }
                }
                if (nodes[i]->neighbours.empty()) {
                    cout << nodes[i]->name << endl;
                }
            }
            cout << "}" << endl;
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
    return 0;
}