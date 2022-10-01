#include <iostream>
#include <string>
#include <regex>

using namespace std;


int main() {
    string sentences = "Would you go, Ilya, with a newspaper, Kolya, QQ.", tmp;
    const regex r(R"(, (\w+),)");
    smatch m;

    if (regex_search(sentences, m, r)) {
        cout << "len" << m.size() << " " << m[0].str()  << " " << m[1].str() << endl;
        for (const auto & i : m) {
            tmp = i.str().substr(2, -1);
            tmp.erase(tmp.size() - 1);
            cout << tmp << endl;
        }
    }
    return 0;
}