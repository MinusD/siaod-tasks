/*
 * Дана строка из заглавных букв латинского алфавита.
 * Найти длину наибольшего палиндрома, который можно получить вычеркиванием некоторых букв из данной строки.
 *
 * Решить задачу с помощью динамического программирования.
 *
 * Математическая модель решения:
 * 1. Построить таблицу, в которой в ячейке [i, j] будет храниться длина наибольшего палиндрома, который можно получить из подстроки s[i..j].
 * 2. Заполнить таблицу по диагоналям, начиная с главной.
 * 3. Найти максимальное значение в таблице.
 *
 * Как работает матрица:
 * 1. Если i == j, то это один символ, а значит это палиндром.
 * 2. Если i + 1 == j, то это два символа, а значит это палиндром, если они равны.
 * 3. Если i + 1 < j, то это больше двух символов, а значит это палиндром, если s[i] == s[j] и s[i + 1..j - 1] - палиндром.
 *
 */

#include <iostream>
#include <string>

using namespace std;


int main() {
    srand(time(nullptr));
    string s;

    // Генерация строки
    for (int i = 0; i < 100; i++) {
        s += 'A' + rand() % 26;
    }
//    s = "ABCCBEA";

    // Вывод строки
    cout << s << endl;

    // Создание таблицы
    int n = s.length();
    int dp[n][n];

    // Заполнение таблицы
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = 0;

    // Заполнение главной диагонали
    for (int i = 0; i < n; i++)
        dp[i][i] = 1;
    // Заполнение диагоналей, параллельных главной
    for (int i = 0; i < n - 1; i++)
        // Если символы совпадают, то длина палиндрома равна 2
        if (s[i] == s[i + 1])
            dp[i][i + 1] = 2;
        else
            // Иначе длина палиндрома равна 1
            dp[i][i + 1] = 1;
    // Заполнение остальных ячеек
    for (int i = 2; i < n; i++)
        // i - длина палиндрома
        for (int j = 0; j < n - i; j++)
            // j - начало палиндрома
            if (s[j] == s[j + i]) // Если символы совпадают
                dp[j][j + i] = dp[j + 1][j + i - 1] + 2; // Длина палиндрома равна длине палиндрома без первого и последнего символа + 2
            else
                dp[j][j + i] = max(dp[j + 1][j + i], dp[j][j + i - 1]); // Иначе длина палиндрома равна максимальной длине палиндрома, полученного из двух подпалиндромов
    cout << dp[0][n - 1] << endl; // Вывод ответа

    // Вывод таблицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << dp[i][j] << " ";
        cout << endl;
    }

    // Вывод самого длинного палиндрома
    int i = 0, j = n - 1;
    while (i < j) {
        if (s[i] == s[j]) {
            cout << s[i];
            i++;
            j--;
        } else if (dp[i + 1][j] > dp[i][j - 1])
            i++;
        else
            j--;
    }
    return 0;
}