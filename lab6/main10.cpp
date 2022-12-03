/*
 * Algorithm of Shannon-Fano
 */

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Symbol {
    char symbol;
    int frequency;
    string code;

    Symbol(char s, char f) : symbol(s), frequency(f) {};
};

class Encoder {
    string text; // Text to encode
    string encodedText; // Encoded text
    int length; // Length of text
    vector<Symbol> symbols; // Symbols
public:
    explicit Encoder(string text) : text(text), length(text.size()) {}

    void encode() {
        // Get symbols
        for (int i = 0; i < length; i++) {
            bool found = false;
            for (auto &symbol: symbols)
                if (symbol.symbol == text[i]) { symbol.frequency++; found = true; break; }
            if (!found) symbols.emplace_back(text[i], 1);
        }

        // Sort symbols by frequency
        sort(symbols.begin(), symbols.end(), [](const Symbol &a, const Symbol &b) {
            return a.frequency > b.frequency;
        });

        if (symbols.empty()) return;

        // Get codes
        codes(0, symbols.size() - 1);

        // Encode text
        for (int i = 0; i < length; i++)
            for (auto &symbol: symbols)
                if (symbol.symbol == text[i]) { encodedText += symbol.code; break; }
    }

    void codes(int lb, int rb) {
        /*
         * Recursive function for getting codes
         */
        if (rb - 1 == lb) { symbols[lb].code += "0"; symbols[rb].code += "1"; return; }
        if (lb == rb) return;

        int different = INT_MAX, mb = rb, ls = 0, rs = 0;
        while (mb > lb) {
            ls += symbols[mb].frequency; rs = 0;
            for (int i = mb - 1; i >= lb; i--) rs += symbols[i].frequency;
            if (abs(ls - rs) < different) different = abs(ls - rs);
            else break;
            mb--;
        }
        for (int i = lb; i <= rb; i++) {
            if (i <= mb) symbols[i].code += "0";
            else symbols[i].code += "1";
        }

        codes(lb, mb);
        codes(mb + 1, rb);
    }

    void printTable() {
        /*
         * Print table of symbols and codes
         */
        for (auto &symbol: symbols) {
            cout << symbol.symbol << " " << symbol.frequency << " " << symbol.code << endl;
        }
    }

    void statistics() {
        cout << "Length: " << length << endl
             << "Text size: " << length * 8 << " bits" << endl
             << "Encoded size: " << encodedText.size() << " bits" << endl
             << "Compression ratio: " << (double) encodedText.size() / (length * 8) << endl;
    }

    string getEncodedText() {
        return encodedText;
    }

    string decode(const string& basicString) {
        string decodedText;
        for (int i = 0; i < basicString.size(); i++) {
            for (auto &symbol: symbols) {
                if (symbol.code == basicString.substr(i, symbol.code.size())) {
                    decodedText += symbol.symbol; i += symbol.code.size() - 1; break;
                }
            }
        }
        return decodedText;
    }
};

int main() {
    string text = "lukovnikov dmitry romanovich lukovnikov dmitry romanovich lukovnikov dmitry romanovich lukovnikov dmitry romanovich lukovnikov dmitry romanovich lukovnikov dmitry romanovich lukovnikov dmitry romanovich lukovnikov dmitry romanovich lukovnikov dmitry romanovich lukovnikov dmitry romanovich";
    Encoder encoder(text);
    encoder.encode();
    encoder.printTable();
    encoder.statistics();
    cout << encoder.getEncodedText() << endl;
    cout << encoder.decode(encoder.getEncodedText()) << endl;
    return 0;
}