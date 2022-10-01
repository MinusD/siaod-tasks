#include <iostream>
#include <string>
#include <regex>

using namespace std;

/**
 * Даны две строки a и b. Требуется найти максимальную длину
 * префикса строки a, который входит как подстрока в строку b. При
 * этом считать, что пустая строка является подстрокой любой
 * строки. Реализация алгоритмом Кнута-Мориса-Пратта.
 * @return длина префикса
 */

int max(int a, int b) {
    /**
     * Returns the maximum of two numbers
     * @param a - first number
     * @param b - second number
     * @return maximum of two numbers
     */
    return a > b ? a : b;
}

int main() {
    // Ввод строк
    string a, b;
    cin >> a >> b;
    // Подготовка массива префикс-функции
    int n = a.length();
    int m = b.length();
    int *pi = new int[n];
    // Вычисление префикс-функции
    pi[0] = 0;

    // Переменные для хранения промежуточных значений
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && a[i] != a[j]) {
            j = pi[j - 1];
        }
        if (a[i] == a[j]) {
            j++;
        }
        pi[i] = j;
    }
    int j = 0;
    int ans = 0;
    // Поиск ответа
    for (int i = 0; i < m; i++) {
        while (j > 0 && b[i] != a[j]) {
            j = pi[j - 1];
        }
        if (b[i] == a[j]) {
            j++;
        }
        // Если префикс найден, то обновляем ответ
        ans = max(ans, j);
    }
    cout << ans;
    return 0;
}
/*
int main() {
    string a, b;
    int maxLen = 0, index = 0;
    string sentences = "Would you go, Ilya, with a newspaper, Kolya, QQ.", tmp;

    return 0;
}*/