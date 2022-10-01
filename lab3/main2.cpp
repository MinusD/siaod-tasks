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

int main() {
    string a, b;
    int maxLen = 0, index = 0;
    string sentences = "Would you go, Ilya, with a newspaper, Kolya, QQ.", tmp;
    const regex r(R"(, (\w+),)");
    smatch match;
    while (regex_search(sentences, match, r)) {
        // Trim commas from the string
        tmp =  match.str(0).substr(2, -1);
        tmp.erase(tmp.size() - 1);
        cout << tmp << endl;

        // Suffix to find the rest of the string
        sentences = match.suffix().str();
    }
    return 0;
}