#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Node {
    int offset;
    int length;
    char next;

    Node(int of, int le, char ne) {
        offset = of;
        length = le;
        next = ne;
    }
};

vector<Node*> Encode(string s) {
    vector<Node*> answer;

    int position = 0;

    while (position < s.length()) {
        int max_index = 0;
        int max_length = 0;
        int cur_index;
        int cur_length;
        for (int j = 0; j < position; j++) {
            cur_index = j, cur_length = 0;

            while (s[cur_index] == s[cur_length + position] && cur_index < s.length()) {
                cur_index++;
                cur_length++;
            }

            if (cur_length > max_length) {
                max_index = position - j;
                max_length = cur_length;
            }
        }

        position += max_length;
        answer.push_back(new Node(max_index, max_length, s[position]));
        position++;
    }

    return answer;
}

int main() {
    string input = "0010100110010000001";
    //string input = "0100001000000100001";

    vector<Node*> encoded = Encode(input);

    for (auto& node : encoded) {
        cout << node->offset << " " << node->length << " " << node->next << "  ";
    }

    return 0;
}