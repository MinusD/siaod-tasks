/*
 * Кодирование информации методом Шеннона Фано
 *
 * Входные данные: строка, состоящая из символов латинского алфавита
 *
 * Выходные данные:
 */
#include <iostream>
#include <vector>

using namespace std;

// Структура для хранения символа и его частоты
struct SymbolFrequency {

    // Символ
    string sym;

    // Частота встречаемости символа
    float pro{};
    int arr[20]{};
    int top{};
} p[20];

typedef struct SymbolFrequency node;

// get frequency some char in string
int getFrequency(string c, string s) {
    int n = 0;
    int len = s.length();
    for (size_t i = 0; i < len; i++) {
        if (string(1, s[i]) == c) {
            n++;
        }
    }

    return n;
}

// function to find shannon code
void shannon(int l, int h, SymbolFrequency p[]) {
    float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
    int i, d, k, j;
    if ((l + 1) == h || l == h || l > h) {
        if (l == h || l > h)
            return;
        p[h].arr[++(p[h].top)] = 0;
        p[l].arr[++(p[l].top)] = 1;
        return;
    } else {
        for (i = l; i <= h - 1; i++)
            pack1 = pack1 + p[i].pro;
        pack2 = pack2 + p[h].pro;
        diff1 = pack1 - pack2;
        if (diff1 < 0)
            diff1 = diff1 * -1;
        j = 2;
        while (j != h - l + 1) {
            k = h - j;
            pack1 = pack2 = 0;
            for (i = l; i <= k; i++)
                pack1 = pack1 + p[i].pro;
            for (i = h; i > k; i--)
                pack2 = pack2 + p[i].pro;
            diff2 = pack1 - pack2;
            if (diff2 < 0)
                diff2 = diff2 * -1;
            if (diff2 >= diff1)
                break;
            diff1 = diff2;
            j++;
        }
        k++;
        for (i = l; i <= k; i++)
            p[i].arr[++(p[i].top)] = 1;
        for (i = k + 1; i <= h; i++)
            p[i].arr[++(p[i].top)] = 0;

        // Invoke shannon function
        shannon(l, k, p);
        shannon(k + 1, h, p);
    }
}

// Function to sort the symbols
// based on their probability or frequency
void sortByProbability(int n, SymbolFrequency p[]) {
    int i, j;
    SymbolFrequency temp;
    for (j = 1; j <= n - 1; j++) {
        for (i = 0; i < n - 1; i++) {
            if ((p[i].pro) > (p[i + 1].pro)) {
                temp.pro = p[i].pro;
                temp.sym = p[i].sym;

                p[i].pro = p[i + 1].pro;
                p[i].sym = p[i + 1].sym;

                p[i + 1].pro = temp.pro;
                p[i + 1].sym = temp.sym;
            }
        }
    }
}

// function to display shannon codes
void display(int n, SymbolFrequency p[]) {
    int i, j;
    cout << "\n\n\n\tSymbol\tProbability\tCode";
    for (i = n - 1; i >= 0; i--) {
        cout << "\n\t" << p[i].sym << "\t\t" << p[i].pro << "\t";
        for (j = 0; j <= p[i].top; j++)
            cout << p[i].arr[j];
    }
}


// function to get shannon codes
string getShannonCode(string s, int n, SymbolFrequency p[]) {
    int i, j, k, l;
    string result;
    for (k = 0; k < s.size(); ++k) {
        for (i = n - 1; i >= 0; i--) {
            if (p[i].sym == string(1, s[k])) {
                string str;
                for (l = 0; l <= p[i].top; l++)
                    str += to_string(p[i].arr[l]);
                result += str;
                break;
            }
        }
    }
    return result;
}


// main code
int main() {
    int n, i, j;
    float total = 0;
    string ch;
    SymbolFrequency temp;

    string toCode = "ninerinineri njingwebr wakmc fwperiogj rtnuinbi jnriwurnternenma infmaewifn ejinrf ijwenar "
                    "gunwerignrtiuirtn vnfjnsdk jnjj  n iudsuin sudhb suhdfbfsh bsdfusbdfuhsbshu bubsubsufvyqerb"
                    "veinc mcasidc jnsdivcneiurnuerinviu webrvbsdjn cjsadnvjineriufreiw nidfbv beriuvbgwei ksdnj"
                    "mcok nmvireuhnviwei";
//    string toCode = "abc abcd abafdjl";

    // Input number of symbols
    cout << "start number of symbols\t: ";
    n = toCode.length();
    cout << n << endl;

    // uniq
    int uniq = 0;


    vector<int> x;
    string buffer = "";
    int counter = 0;
    // Input symbols
    for (i = 0; i < n; i++) {
        cout << "symbol " << i + 1 << " : ";
        ch = toCode[i];
        cout << ch << endl;

        // TODO: убрать повторения
        if (buffer.find(ch) == string::npos) {
            x.push_back(getFrequency(ch, toCode));
            // Insert the symbol to Node
            p[uniq].sym += ch;
            ++uniq;
        }

        buffer += ch;


    }

    // Input probability of symbols
    for (i = 0; i < uniq; i++) {
        cout << "\nprobability of " << p[i].sym << " : ";
        cout << x[i] << endl;

        // Insert the value to Node
        p[i].pro = x[i];
        total = total + p[i].pro;

        // checking max probability
        if (total > n) {
            cout << "Invalid. Enter new values";
            total = total - p[i].pro;
            i--;
        }
    }

    p[i].pro = 1 - total;

    // Sorting the symbols based on
    // their probability or frequency
    sortByProbability(uniq, p);

    for (i = 0; i < uniq; i++)
        p[i].top = -1;

    // Find the shannon code
    shannon(0, uniq - 1, p);

    // Display the codes
    display(uniq, p);


    string res = getShannonCode(toCode, uniq, p);
    cout << "\nИсходный размер сообщения: " << n * 8 << " бит\n";
    cout << "Размер сжатого сообщения: " << res.length() << " бит\n";
    cout << "Коэффициент сжатия: " << (double) res.length() / (n * 8) << "\n";

    cout << "\nshannon code:\n";
    cout << res << endl;
    return 0;
}
