/*
 * Метод - метод ветвей и границ
 *
 * Замок имеет прямоугольную форму и разделен на
 * M*N клеток (M<=50; N>=50). Каждая клетка может иметь от 0 до 4 стен, отделяющих комнаты.
 * Определить:
 * - количество комнат в замке;
 * - площадь наибольшей комнаты;
 * - какую стену следует удалить, чтобы получить
 * комнату наибольшей площади.
 *
 */

#include <iostream>
#include <vector>
#include <iomanip>


using namespace std;

class Castle {
    int M, N; // Размеры замка
    vector<vector<int>> castle; // План замка
    vector<vector<bool>> visited; // Посещенные клетки
    int rooms; // Количество комнат
    int maxRoom; // Площадь наибольшей комнаты
    int maxRoomI, maxRoomJ; // Координаты наибольшей комнаты
    int maxRoomWallI{}, maxRoomWallJ{}; // Координаты стены наибольшей комнаты после удаления
    int maxRoomWall{}; // Направление стены наибольшей комнаты после удаления
    vector<int> roomsSizes; // Площадь комнат
    vector<vector<int>> roomsMap; // Карта комнат

    // Проверка, что клетка находится внутри замка
    bool inCastle(int i, int j) const {
        return i >= 0 && i < M && j >= 0 && j < N;
    }

    // Проверка, что клетка не посещена
    bool notVisited(int i, int j) {
        return !visited[i][j];
    }

    // Проверка, что клетка не имеет стены
    bool notWall(int i, int j, int wall) {
        /*
         * 1 - стена сверху - 0001
         * 2 - стена справа - 0010
         * 4 - стена снизу - 0100
         * 8 - стена слева - 1000
         */
        // Проверка на вхождение в замок
        if (!inCastle(i, j)) return false;
        // Проверка на стену
        return (castle[i][j] & wall) == 0;
    }

    // Проверка, что клетка не имеет стены
    bool checkWall(int i, int j, const string &str) {
        if (str == "up") {
            return notWall(i, j, 1);
        } else if (str == "right") {
            return notWall(i, j, 2);
        } else if (str == "down") {
            return notWall(i, j, 4);
        } else if (str == "left") {
            return notWall(i, j, 8);
        }
        return false;
    }

public:

    // Конструктор
    Castle(int M, int N) : M(M), N(N) {
        visited.resize(M); // Выделение памяти под вектор посещенных клеток
        roomsMap.resize(M); // Выделение памяти под вектор карты комнат
        for (int i = 0; i < M; i++) {
            visited[i].resize(N);
            roomsMap[i].resize(N);
        }
        rooms = 0;
        maxRoom = 0;
        maxRoomI = 0;
        maxRoomJ = 0;
        maxRoomWall = 0;
    }

    // Генерация замка
    void generate() {
        castle.resize(M);
        for (int i = 0; i < M; i++) {
            castle[i].resize(N);
            for (int j = 0; j < N; j++) {
                castle[i][j] = rand() % 16;
            }
        }

        // Установка стен вокруг замка
        for (int i = 0; i < M; i++) {
            castle[i][0] |= 8; // Стена слева
            castle[i][N - 1] |= 2; // Стена справа
        }
        for (int j = 0; j < N; j++) {
            castle[0][j] |= 1; // Стена сверху
            castle[M - 1][j] |= 4; // Стена снизу
        }

        castle[0][0] = 15;

        // Улаживание конфликтов стен с соседними клетками
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (castle[i][j] & 1) {
                    // Стена сверху
                    if (notWall(i - 1, j, 4)) castle[i][j] ^= 1;
                }
                if (castle[i][j] & 2) {
                    // Стена справа
                    if (notWall(i, j + 1, 8)) castle[i][j] ^= 2;
                }
                if (castle[i][j] & 4) {
                    // Стена снизу
                    if (notWall(i + 1, j, 1)) castle[i][j] ^= 4;
                }
                if (castle[i][j] & 8) {
                    // Стена слева
                    if (notWall(i, j - 1, 2)) castle[i][j] ^= 8;
                }
            }
        }
    }

    // Вывод замка
    void print() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(2) << castle[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Графический вывод замка
    void printGraph() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cout << "+";
                if (castle[i][j] & 1) cout << "---"; // Стена сверху
                else cout << "   ";
            }
            cout << "+" << endl;
            for (int j = 0; j < N; j++) {
                if (castle[i][j] & 8) cout << "|"; // Стена слева
                else cout << " ";
                if (visited[i][j]) cout << " * ";
                else cout << "   ";
            }
            if (castle[i][N - 1] & 2) cout << "|"; // Стена справа
            else cout << " ";
            cout << endl;
        }
        for (int j = 0; j < N; j++) {
            cout << "+";
            if (castle[M - 1][j] & 4) cout << "---"; // Стена снизу
            else cout << "   ";
        }
        cout << "+" << endl;
    }

    // Поиск комнат
    void findRooms() {
        int roomNumber = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (notVisited(i, j)) {
                    rooms++;
                    int room = 0;
                    findRoom(i, j, room, roomNumber);

                    // Заполнение площадей комнат
                    roomsSizes.push_back(room);
                    roomNumber++;

                    if (room > maxRoom) {
                        maxRoom = room;
                        maxRoomI = i;
                        maxRoomJ = j;
                    }
                }

            }
        }
    }

    // Поиск комнаты
    void findRoom(int i, int j, int &room, int roomNumber = 0) {
        room++;
        visited[i][j] = true;
        roomsMap[i][j] = roomNumber;

        if (checkWall(i, j, "up")) {
            if (notVisited(i - 1, j)) {
                findRoom(i - 1, j, room, roomNumber);
            }
        }

        if (checkWall(i, j, "right")) {
            if (notVisited(i, j + 1)) {
                findRoom(i, j + 1, room, roomNumber);
            }
        }

        if (checkWall(i, j, "down")) {
            if (notVisited(i + 1, j)) {
                findRoom(i + 1, j, room, roomNumber);
            }
        }

        if (checkWall(i, j, "left")) {
            if (notVisited(i, j - 1)) {
                findRoom(i, j - 1, room, roomNumber);
            }
        }
    }

    // Поиск стены, которую нужно удалить, чтобы получить наибольшую комнату
    void findMaxRoomWall() {
        int maxRoomWallTmp = 0, tmpRoom = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {

                if (!checkWall(i, j, "up") && inCastle(i - 1, j)) {
                    if (roomsMap[i][j] != roomsMap[i - 1][j]) {
                        tmpRoom = roomsSizes[roomsMap[i][j]] + roomsSizes[roomsMap[i - 1][j]];
                        if (tmpRoom > maxRoomWallTmp) {
                            maxRoomWallTmp = tmpRoom;
                            maxRoomWallI = i;
                            maxRoomWallJ = j;
                            maxRoomWall = 1;
                        }
                    }
                }

                if (!checkWall(i, j, "right") && inCastle(i, j + 1)) {
                    if (roomsMap[i][j] != roomsMap[i][j + 1]) {
                        tmpRoom = roomsSizes[roomsMap[i][j]] + roomsSizes[roomsMap[i][j + 1]];
                        if (tmpRoom > maxRoomWallTmp) {
                            maxRoomWallTmp = tmpRoom;
                            maxRoomWallI = i;
                            maxRoomWallJ = j;
                            maxRoomWall = 2;
                        }
                    }
                }

                if (!checkWall(i, j, "down") && inCastle(i + 1, j)) {
                    if (roomsMap[i][j] != roomsMap[i + 1][j]) {
                        tmpRoom = roomsSizes[roomsMap[i][j]] + roomsSizes[roomsMap[i + 1][j]];
                        if (tmpRoom > maxRoomWallTmp) {
                            maxRoomWallTmp = tmpRoom;
                            maxRoomWallI = i;
                            maxRoomWallJ = j;
                            maxRoomWall = 4;
                        }
                    }
                }

                if (!checkWall(i, j, "left") && inCastle(i, j - 1)) {
                    if (roomsMap[i][j] != roomsMap[i][j - 1]) {
                        tmpRoom = roomsSizes[roomsMap[i][j]] + roomsSizes[roomsMap[i][j - 1]];
                        if (tmpRoom > maxRoomWallTmp) {
                            maxRoomWallTmp = tmpRoom;
                            maxRoomWallI = i;
                            maxRoomWallJ = j;
                            maxRoomWall = 8;
                        }
                    }
                }
            }
        }
    }

    // Вывод карты комнат
    void printRoomsMap() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cout << roomsMap[i][j] << " ";
            }
            cout << endl;
        }
    }


    // Вывод результата
    void printResult() const {
        cout << "Количество комнат: " << rooms << endl;
        cout << "Площадь наибольшей комнаты: " << maxRoom << endl;
        cout << "Координаты наибольшей комнаты: " << maxRoomI << " " << maxRoomJ << endl;
        cout << "Координаты стены, которую нужно удалить, чтобы получить наибольшую комнату: " << maxRoomWallI << " "
             << maxRoomWallJ << endl;
        cout << "Направление стены, которую нужно удалить, чтобы получить наибольшую комнату: ";
        switch (maxRoomWall) {
            case 1:
                cout << "up";
                break;
            case 2:
                cout << "right";
                break;
            case 4:
                cout << "down";
                break;
            case 8:
                cout << "left";
                break;
        }
        cout << endl;
    }
};

int main() {
    srand(time(nullptr));

    int M = 5, N = 5;
//    cin >> M >> N;
    Castle castle(M, N);
    castle.generate();
    castle.print();
    castle.printGraph();
    castle.findRooms();
    castle.printRoomsMap();
    castle.findMaxRoomWall();
    castle.printResult();
    return 0;
}
