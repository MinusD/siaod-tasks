#include <iostream>
#include <string>
#include <regex>

using namespace std;

/**
 * This function is used to find the appeals in a string
 * @param str - the string to search
 * @return found words
 */
 * @return
 */
int main() {
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