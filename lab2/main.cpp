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

    virtual bool isAlive() { return true; }
};

class PoliceDelete : public InsurancePolicy {
public:
    PoliceDelete() : InsurancePolicy(0, "", "") {}


    bool isAlive() override { return false; }
};


class HashTable {
    int size;
    int filled;
    int deleted;
    vector<InsurancePolicy *> data;
    PoliceDelete *deleteFlag;

public:
    // Constructor with one param (explicit)
    explicit HashTable(int size = 10) : size(size), filled(0), deleted() {
        data.resize(size);
        deleteFlag = new PoliceDelete();
    }

    bool add(InsurancePolicy *insurancePolicy) {
        if (float(filled + deleted) / float(size) > MAX_FILLED) rehash();

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
        cout << "[ Size: " << size << " | Filled: " << filled << " | Deleted: " << deleted << " ] \n";
        showTableSeparator(numSize);
        cout << "| Code" << string(numSize - 3, ' ') << "| Number           | Company       | Surname       | \n";
        showTableSeparator(numSize);

        for (int i = 0; i < size; ++i) {
            if (data[i] && data[i]->isAlive()) {
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
        data.clear();
        filled = 0;
        deleted = 0;
        size *= 2;
        data.resize(size);
        for (auto el: data_t) {
            if (el && el->isAlive()) add(el);
        }
    }

    int getCodeByPoliceNumber(unsigned long long policyNumber) {
        for (int i = 0; i < size; ++i) {
            int code = (hashFunction(policyNumber) + i * i * CONST_K) % size;
            if (data[code] && data[code]->number == policyNumber) {
                return code;
            }
        }
        return -1;
    }

    bool deleteByPolicyNumber(unsigned long long policyNumber) {
        int code = getCodeByPoliceNumber(policyNumber);
        if (code != -1) {
            cout << code << endl;
            InsurancePolicy *policy_t = data[code];
            data[code] = deleteFlag;
            deleted++;
            filled--;
            return true;
        } else {
            return false;
        }
    }

    InsurancePolicy *getPolicyByNumber(unsigned long long policyNumber) {
        int code = getCodeByPoliceNumber(policyNumber);
        if (code != -1) {
            return data[code];
        } else
            return nullptr;
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
    int ex = -1, size_t;
    unsigned long long number_t;
    string company_t, surname_t;
    while (ex) {
//        system("cls");
        cout << "1. Random generate list\n"
                "2. Hand input \n"
                "3. Delete by policy number\n"
                "4. Show table\n"
                "5. Show table with empty rows\n"
                "6. Show policy info by number\n"
                "0. Exit\n";
        cin >> ex;
        switch (ex) {
            case 1:
                cout << "New entries:";
                cin >> size_t;
                generateList(table, size_t);
                break;
            case 2:
                cout << "Enter Police number, Company and Surname\n";
                cin >> number_t >> company_t >> surname_t;
                if (!table.add(new InsurancePolicy(number_t, company_t, surname_t)))
                    cout << "A policy with this number already exists.\n";
                break;
            case 3:
                cout << "Enter the number of the policy to be removed\n";
                cin >> number_t;
                if (!table.deleteByPolicyNumber(number_t))
                    cout << "There is no policy with this number.\n";
                break;
            case 4:
                table.showTable();
                break;
            case 5:
                table.showTable(true);
                break;
            case 6:
                cout << "Enter the required policy number\n";
                cin >> number_t;
                InsurancePolicy *policy_t;
                policy_t = table.getPolicyByNumber(number_t);
                if (policy_t) {
                    cout << *policy_t << endl;
                } else {
                    cout << "There is no policy with this number.\n";
                }
                break;
        }
    }
    return 0;
}