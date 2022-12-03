/*
 * Algorithm of Huffman
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    /*
     * Node of Huffman tree
     */
    Node *left, *right;
    int frequency;
    char symbol;
    string code;

    Node(int frequency, char symbol) : frequency(frequency), symbol(symbol) {
        left = right = nullptr;
    }
};

class Encoder {
    string text; // Text to encode
    string encodedText; // Encoded text
    int length; // Length of text

    vector<Node *> nodes; // Nodes of Huffman tree
    Node *root; // Root of Huffman tree

public:
    explicit Encoder(const string &text) : text(text), length(text.length()) {}

    void encode(){
        /*
         * Encoding text
         */

        // Get frequency of each symbol
        for (int i = 0; i < length; i++) {
            bool found = false;
            for (auto &node: nodes)
                if (node->symbol == text[i]) { node->frequency++; found = true; break; }
            if (!found) nodes.emplace_back(new Node(1, text[i]));
        }

        // Sort nodes by frequency
        sort(nodes.begin(), nodes.end(), [](const Node *a, const Node *b) {
            return a->frequency > b->frequency;
        });

        if (nodes.empty()) return;

        // Build Huffman tree
        while (nodes.size() > 1) {
            Node *left = nodes.back(); nodes.pop_back();
            Node *right = nodes.back(); nodes.pop_back();
            Node *parent = new Node(left->frequency + right->frequency, 0);
            parent->left = left;
            parent->right = right;
            nodes.emplace_back(parent);
            sort(nodes.begin(), nodes.end(), [](const Node *a, const Node *b) {
                return a->frequency > b->frequency;
            });
        }
        root = nodes.back(); nodes.pop_back();

        // Get codes
        codes(root, "");

        // Encode text
        for (int i = 0; i < length; i++)
            encodedText += getCode(text[i], root);
    }

    void codes(Node *node, string code){
        /*
         * Recursive function for getting codes
         */
        if (node->left == nullptr || node->right == nullptr) { node->code = code; return; }
        codes(node->left, code + "0");
        codes(node->right, code + "1");
    }

    string getCode(char symbol, Node *cur) {
        /*
         * Find code of symbol
         */
        if (cur->symbol == symbol) return cur->code;
        if (cur->left != nullptr) {
            string code = getCode(symbol, cur->left);
            if (code != "") return code;
        }
        if (cur->right != nullptr) {
            string code = getCode(symbol, cur->right);
            if (code != "") return code;
        }
        return "";
    }



    string decode(string basicString){
        /*
         * Decoding text
         */
        string decodedText;
        Node *node = root;
        for (char i : basicString){
            if (i == '0') node = node->left;
            else node = node->right;
            if (node->left == nullptr && node->right == nullptr){
                decodedText += node->symbol;
                node = root;
            }
        }
        return decodedText;
    }

    void statistics() {
        /*
         * Print statistics
         */
        cout << "Length: " << length << endl
            << "Text size: " << length * 8 << " bits" << endl
            << "Encoded length: " << encodedText.length() << endl
            << "Compression ratio: " << (double) encodedText.length() / (length * 8) << endl;
    }

    const string &getEncodedText() const {
        return encodedText;
    }

    ~Encoder(){
        /*
         * Destructor
         */
        delete root;
    }
};

int main() {
    string text = "lukovnikov dmitry romanovich";
    Encoder encoder(text);
    encoder.encode();
    cout << "Encoded text: " << encoder.getEncodedText() << endl;
    encoder.statistics();
    cout << "Decoded text: " << encoder.decode(encoder.getEncodedText()) << endl;
    return 0;
}

