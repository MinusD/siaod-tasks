/*
 * Дана строка из заглавных букв латинского алфавита.
 * Найти длину наибольшего палиндрома, который можно получить вычеркиванием некоторых букв из данной строки.
 *
 * Решить задачу с помощью динамического программирования.
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;

    // Generate string
    for (int i = 0; i < 100; i++) {
        s += 'A' + rand() % 26;
    }

    int n = s.length();
    int dp[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = 0;
    for (int i = 0; i < n; i++)
        dp[i][i] = 1;
    for (int i = 0; i < n - 1; i++)
        if (s[i] == s[i + 1])
            dp[i][i + 1] = 2;
        else
            dp[i][i + 1] = 1;
    for (int i = 2; i < n; i++)
        for (int j = 0; j < n - i; j++)
            if (s[j] == s[j + i])
                dp[j][j + i] = dp[j + 1][j + i - 1] + 2;
            else
                dp[j][j + i] = max(dp[j + 1][j + i], dp[j][j + i - 1]);
    cout << dp[0][n - 1];
    return 0;
}