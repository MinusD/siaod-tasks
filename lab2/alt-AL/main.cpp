/**
 * Алсу Гизатуллина - вар.14
 */

#include <iostream>
#include <utility>
#include <vector>

#define MAX_COEFFICIENT 0.75


using namespace std;

class License {
public:
    unsigned long number;
    string name;
    string founder;

    License(unsigned long number, string name, string founder) : number(number), name(std::move(name)),
                                                                 founder(std::move(founder)) {}

    friend ostream &operator<<(ostream &os, const License &license) {
        os << "number: " << license.number << " name: " << license.name << " founder: " << license.founder;
        return os;
    }

    virtual bool nonDelete() {
        return true;
    }
};

class LicenseDel : public License { // Класс для пометки удаления элемента
public:
    LicenseDel() : License(0, "", "") {}

    bool nonDelete() override {
        return false;
    }
};

class Table {
    unsigned long size;
    unsigned long filled;
    unsigned long deleted;
    vector<License *> licenses;
    LicenseDel *licenseDel;
public:
    Table(unsigned long size = 10) : size(size), filled(0), deleted(0) {
        licenseDel = new LicenseDel();
        licenses.resize(size);
    }

    unsigned long getSize() const {
        return size;
    }

    unsigned long getFilled() const {
        return filled;
    }

    bool append(License *license) {
        if (float(filled + deleted + 1) / float(size) > MAX_COEFFICIENT) { // Проверяем, не переполнилась ли таблица
            size *= 2; // Увеличиваем размер таблицы
            rehashTable();
        }

        for (unsigned long i = 0; i < size; ++i) { // Проверяем, уникальный ли номер
            if (licenses[i] != nullptr && licenses[i]->number == license->number) {
                return false;
            }
        }

        for (unsigned long i = 0;; ++i) {
            // Получаем хэш до тех пор, пока не попадём в свободную ячейку
            unsigned long hash = (hashFunc(license->number) + i * hashFuncSecond(license->number)) % size;
            if (licenses[hash] == nullptr) {
                licenses[hash] = license;
                filled++;
                return true;
            }
        }
    }

    string randomStr(const int len) { // Генератор случайных слов
        static const char alphanum[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        std::string tmp_s;
        tmp_s.reserve(len);

        for (int i = 0; i < len; ++i) {
            tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        return tmp_s;
    }

    void generate(int count = 1) { // Генерируем определённое количество рандомных записей
        for (unsigned long i = 0; i < count; ++i) {
            License *tmp = new License(
                    (unsigned long) rand() * rand(),
                    randomStr(8), randomStr(8)
            );
            if (!append(tmp)) { // Если случайно совпал немер, не учитываем его
                i--;
            }
        }
    }

    unsigned long hashFunc(unsigned long number) { // Первая хэш функция
        return number % size;
    }

    unsigned long hashFuncSecond(unsigned long number) { // Вторая хэш функция
        return number * 23 % size;
    }

    void rehashTable() { // Рехеширование таблицы
        vector<License *> licensesTmp = licenses; // Копируем данные
        filled = 0;
        deleted = 0;
        licenses.clear();
        licenses.resize(size);
        for (unsigned long i = 0; i < licensesTmp.size(); ++i) { // Проверям, что они не удалены и вносим заново
            if (licensesTmp[i] != nullptr && licensesTmp[i]->nonDelete()) {
                append(licensesTmp[i]);
            }
        }
    }

    bool handRehash(unsigned long newSize) {
        if (float(filled) / float(newSize) > MAX_COEFFICIENT) { // Проверяем можем ли мы изменить размер
            size = newSize;
            rehashTable();
        }
    }

    void print() {
        cout << "Хэш, номер лицензии, название, поручитель" << endl;
        for (unsigned long i = 0; i < size; ++i) {
            if (licenses[i] != nullptr && licenses[i]->nonDelete()) {
                cout << i << " " << licenses[i]->number << " " << licenses[i]->name << " " << licenses[i]->founder
                     << endl;
            }
        }
    }

    bool del(unsigned long number) { // Удаление лицензии её номеру
        for (unsigned long i = 0;i < size; ++i) {
            unsigned long hash = (hashFunc(number) + i * hashFuncSecond(number)) % size;
            if (licenses[hash] != nullptr && licenses[hash]->number == number) {
                License *license = licenses[hash];
                licenses[hash] = licenseDel;
                deleted++;
                filled--;
                return true;
            }
        }
        return false;
    }

    License *getLicense(unsigned long number) { // Получение лицензии её номеру
        for (unsigned long i = 0; i < size; ++i) {
            unsigned long hash = (hashFunc(number) + i * hashFuncSecond(number)) % size;
            if (licenses[hash] != nullptr && licenses[hash]->number == number) {
                return licenses[hash];
            }
        }
        return nullptr;
    }

};

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    Table table;
    License *tmpLicence;
    int command = 1, tmpInt;
    unsigned long tmpLong;
    string nameTmp, founderTmp;
    for (;;) { // Бесконечный цикл
        switch (command) {
            case 1:
                cout << "Меню: \n1 - Показать меню\n2 - Добавить элемент\n3 - Сгенерировать несколько элементов\n"
                        "4 - Показать таблицу\n5 - Изменить размер таблицы\n6 - Поиск по номеру\n7 - Удалить по номеру\n"
                        "8 - Выход\n";
                break;
            case 2:
                cout << "Введите номер лицензии, название и поручителя" << endl;
                cin >> tmpLong >> nameTmp >> founderTmp;
                if (table.append(new License(tmpLong, nameTmp, founderTmp))) {
                    cout << "Лицензия добавлена успешно!" << endl;
                } else {
                    cout << "Лицензия не добавлена, что-то пошло не так" << endl;
                }
                break;
            case 3:
                cout << "Сколько записей генерируем?" << endl;
                cin >> tmpInt;
                table.generate(tmpInt);
                break;
            case 4:
                table.print();
                break;
            case 5:
                cout << "Новый размер: " << endl;
                cin >> tmpLong;
                if (table.handRehash(tmpLong)) {
                    cout << "Размер изменён" << endl;
                } else {
                    cout << "Размер не изменён" << endl;
                }
                break;
            case 6:
                cout << "Введите номер лицензии: ";
                cin >> tmpLong;
                tmpLicence = table.getLicense(tmpLong);
                if (tmpLicence == nullptr) {
                    cout << "Элемент не найден" << endl;
                } else {
                    cout << *tmpLicence << endl;
                }
                break;
            case 7:
                cout << "Введите номер лицензии: ";
                cin >> tmpLong;
                if (table.del(tmpLong)) {
                    cout << "Элемент удалён" << endl;
                } else {
                    cout << "Элемент не найден" << endl;
                }
                break;
            case 8:
                return 0;
            default:
                cout << "Команда не найдена";
                break;
        }
        cin >> command;
    }


    return 0;
}