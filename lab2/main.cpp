//
// Created by Lukov on 17.09.2022.
//

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

#define BORDER_BOTTOM 1000000000000000
#define BORDER_TOP 9999999999999999
#define MAX_FILLED 0.75
#define CONST_K 1

using namespace std;


class InsurancePolicy {
public:
    unsigned long long number;
    string company;
    string surname;

    InsurancePolicy(unsigned long long number, string company, string surname) : number(number),
                                                                                 company(move(company)),
                                                                                 surname(move(surname)) {}

    bool operator==(const InsurancePolicy &rhs) const {
        return number == rhs.number &&
               company == rhs.company &&
               surname == rhs.surname;
    }

    bool operator!=(const InsurancePolicy &rhs) const {
        return !(rhs == *this);
    }

    friend ostream &operator<<(ostream &os, const InsurancePolicy &policy) {
        os << "number: " << policy.number << " company: " << policy.company << " surname: " << policy.surname;
        return os;
    }
};


class HashTable {
    int size;
    int filled;
    vector<InsurancePolicy *> data;

public:
    // Constructor with one param (explicit)
    explicit HashTable(int size = 10) : size(size), filled(0) {
        data.resize(size);
    }

    bool add(InsurancePolicy *insurancePolicy) {
        if (float(filled) / float(size) > MAX_FILLED) rehash();

        // Code uniqueness check
        for (auto el: data)
            if (el && el->number == insurancePolicy->number)
                return false;

        for (int i = 0; i < size; ++i) {

            int code = (hashFunction(insurancePolicy->number) + i * i * CONST_K) % size;

            if (data[code] == NULL) {
                data[code] = insurancePolicy;
                break;
            }
        }
        filled++;
        return true;
    }

    void showTableSeparator(int numSize) {
        cout << '+' << string(numSize + 2, '-') << '+' << string(18, '-') << '+' << string(15, '-') <<
             '+' << string(15, '-') << "+\n";
    }

    void showTable(bool withEmpty = false) {

        int numSize = to_string(size).size();
        numSize = (numSize < 4 ? 4 : numSize);
        showTableSeparator(numSize);
        cout << "| Code" << string(numSize - 3, ' ') << "| Number           | Company       | Surname       | \n";
        showTableSeparator(numSize);


        for (int i = 0; i < size; ++i) {
            if (data[i]) {
                printf("| %0*d | %016lld | %-13s | %-13s | \n", numSize, i, data[i]->number, data[i]->company.c_str(),
                       data[i]->surname.c_str());
            } else if (withEmpty) {
                printf("| %0*d | %16s | %13s | %13s | \n", numSize, i, "", "", "");
            }
        }
        showTableSeparator(numSize);
    }

    int hashFunction(unsigned long long police) {
        return (int) (police % size);
    }

    void rehash() {
        vector<InsurancePolicy *> data_t = data;
        size *= 2;
        for (int i = 0; i < size; ++i) {
            
        }
    }

//    virtual ~HashTable() {
//        for (auto el: data) {
//            delete[]el;
//        }
//    }

};


void generateList(HashTable &table, int size = 1) {
    default_random_engine u{};
    uniform_int_distribution<> d{};
    u.seed(random_device()()); // Analog srand
    InsurancePolicy *insurancePolicy;

    for (int i = 0; i < size; ++i) {

        // Capital first letter generation
        vector<char> company_t({char(toupper(char(rand() % 26 + 0x61)))});
        vector<char> surname_t({char(toupper(char(rand() % 26 + 0x61)))});

        // Generate random number of letters
        for (int j = 0; j < d(u, uniform_int_distribution<>::param_type{6, 12}); ++j) {
            company_t.push_back(rand() % 26 + 0x61);
        }
        for (int j = 0; j < d(u, uniform_int_distribution<>::param_type{6, 12}); ++j) {
            surname_t.push_back(rand() % 26 + 0x61);
        }

        // Convert char vector to string
        string company(company_t.begin(), company_t.end());
        string surname(surname_t.begin(), surname_t.end());

        insurancePolicy = new InsurancePolicy(
                BORDER_BOTTOM +
                (((unsigned long long) d(u, uniform_int_distribution<>::param_type{1000000, RAND_MAX}) *
                  (unsigned long long) d(u, uniform_int_distribution<>::param_type{1000000, RAND_MAX})) %
                 (BORDER_TOP - BORDER_BOTTOM)), company, surname
        );
        //cout << *insurancePolicy << endl;

        // Add policy to table
        table.add(insurancePolicy);
    }
}


int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    HashTable table;
    generateList(table, 2);
    table.showTable();
    cout << endl << endl;
    table.add(new InsurancePolicy(1000, "1Ghb", "Gdfs"));
    table.add(new InsurancePolicy(2000, "2Ghb231", "Gdfffs"));
    table.add(new InsurancePolicy(3000, "3Ghb231", "Gdfffs"));
    table.add(new InsurancePolicy(4000, "4Ghb231", "Gdfffs"));
    table.showTable();
    //table.showTable(true);
    return 0;
}