#include <iostream>
#include <string>
#include <regex>

using namespace std;

/**
 * Даны две строки a и b. Требуется найти максимальную длину
 * префикса строки a, который входит как подстрока в строку b. При
 * этом считать, что пустая строка является подстрокой любой
 * строки. Реализация алгоритмом Кнута-Мориса-Пратта.
 * @return
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

vector<char> stringToVector(string str) {
    /**
     * Converts a string to a vector
     * @param str - string to convert
     * @return vector of chars
     */
    vector<char> vec;
    for (char c: str) {
        vec.push_back(c);
    }
    return vec;
}

vector<int> prefixFunction(vector<char> str) {
    /**
     * Calculates the prefix function for a string
     * @param str - string to calculate
     * @return prefix function
     */
    int n = str.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];

        // Пока не совпадет символ или не дойдем до начала строки
        while (j > 0 && str[i] != str[j]) {
            j = pi[j - 1];
        }

        // Если символы совпали, то увеличиваем значение префикса
        if (str[i] == str[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

void showPrefix(const vector<int> &pi) {
    /**
     * Shows the prefix function
     * @param pi - prefix function
     */
    for (int i: pi) {
        cout << i << " ";
    }
    cout << endl;
}


int main() {
    string as, bs;
    int maxLen = 0, index = 0;
//    as = "aabaa";
//    bs = "aaaaaaba1aaa";
    cin >> as >> bs;

    // Переводим строки в векторы
    vector<char> a = stringToVector(as), b = stringToVector(bs);

    // Генерируем префикс-функцию для строки a
    vector<int> pi = prefixFunction(a);
    for (int i = 0; i < b.size(); i++) {

        while (index > 0 && b[i] != a[index]) {
            index = pi[index - 1];
        }

        // Если символы совпали, то увеличиваем значение префикса
        if (b[i] == a[index]) {
            index++;
            maxLen = max(maxLen, index);
        }

        // Если префикс равен длине строки, то выходим, строка входит целиком
        if (index == a.size()) {
            index = pi[index - 1];
        }
    }
    cout << "Max length: " << maxLen << endl;
    return 0;
}