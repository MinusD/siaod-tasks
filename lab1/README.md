# Лабораторная 1 | Побитовые операторы

### Номер 1.a
Реализуйте вышеприведённый пример, проверьте правильность результата в том числе и на 
других значениях х.

```cpp
cout << "Task 1.a\n";
unsigned char x = 255; // 255 16 (00010000)
unsigned char mask = 1;
x = x & (~(mask << 4));
cout << bitset<8>(x);
```
Для проверки введём число `16`, что в двоичной система `00010000`, после выполнения программы получим `00000000`, следовательно программа работает.

### Номер 1.б
Реализуйте по аналогии с предыдущим примером установку 7-го бита числа в единицу.

```cpp
cout << "\n\nTask 1.б\n";
unsigned char x = 0;
unsigned char mask = 1;
x = x | (mask << 6);
cout << bitset<8>(x);
```
Аналагично предыдущему заданию, только смещение на большее количество бит.

### Номер 1.в
Реализуйте код листинга 1, объясните выводимый программой результат.

```cpp
cout << "\n\nTask 1.в\n";
unsigned int a = 25;
const int n = sizeof(int) * 8;
unsigned maska = (1 << n - 1); // Помещаем 1 в старший разряд
cout << "Start mask: " << bitset<n>(maska) << endl;
cout << "Result: ";
for (int i = 1; i <= n; i++) {
    cout << ((a & maska) >> (n - i));
    maska >>= 1;
}
```

Пррграмма выводит `00000000000000000000000000011001`, если перевести в двоичную сс, то получиться число `25`. Программа изменяя расположение единички в маске, выводит биты переменной `a` начиная со старшего разряда.

### Номер 2.а
 Реализуйте вышеописанный пример с вводом произвольного набора до 8-ми чисел (со значениями от 0 до 7) и его сортировкой битовым массивом в виде числа типа unsigned char. Проверьте работу программы.

```cpp
cout << "\n\nTask 2.а\n";
unsigned char data = 0;
short int size, tmp;
cout << "Enter array size: ";
cin >> size;
for (int i = 0; i < size; i++) 
{
    cin >> tmp;
    data = data | (1 << tmp);
}
//cout << bitset<8>(data) << endl;
cout << "Sorted array: ";
for (int i = 0; i < sizeof(data) * 8; i++)
{
    if ((1 << i) & data) cout << i << " ";
}
```

После того, как ввели размер массива, пробегаемся циклом и с помощию статичной маски (цифра `1`), запоминаем какие цифры мы ввели. Для вывода используем конструкцию работающую по аналагичному принципу. Только вместо дизъюнкции, используем коньюнкцию.

### Номер 2.б
Адаптируйте вышеприведённый пример для набора из 64-х чисел (со начениями от 0 до 63) с битовым массивом в виде числа типа unsigned long long.

```cpp
cout << "\n\nTask 2.б\n";
unsigned long long data = 0, mask = 1;
short int size, tmp;
cout << "Enter array size: ";
cin >> size;
for (int i = 0; i < size; i++)
{
    mask = 1;
    cin >> tmp;
    data = data | (mask << tmp);
}
cout << "Sorted array: ";
for (int i = 0; i < sizeof(data) * 8; i++)
{
    mask = 1;
    if ((mask << i) & data) cout << i << " ";
}
```

Аналагично предыдущему заданию, за исключением того, что `1`, сменились на единичные маски.

### Номер 2.в
Исправьте программу задания 2.б, чтобы для сортировки набора из 64-х чисел использовалось не одно число типа unsigned long long, а линейный массив чисел типа unsigned char.

```cpp
cout << "\n\nTask 2.в\n";
int size, tmp;
vector<unsigned char> data;
cout << "Enter array size: ";
cin >> size;
for (int i = 0; i < 8; i++)
    data.push_back(0);
for (int i = 0; i < size; i++) {
    cin >> tmp;
    data[tmp / 8] = data[tmp / 8] | (1 << (tmp % 8));
}
cout << "Sorted array: ";
for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
        if ((1 << j) & data[i]) cout << i * 8 + j << " ";
```

Посклькую у нас есть фиксированное максиамлбное число (`63`), а размер `unsigned char` 1 байт, то размер вектора всегда будет `8`. Сначала заполняем его польностью нулями, и затем заполняем числами, аналагичноппредыдушим заданием, за тем исключением, что сначала мы обращаемся по индексу.

### Номер 3.а

* **Входные данные:** файл, содержащий не более n=10^7 неотрицательных целых чисел2 , среди них нет повторяющихся. 
* **Результат:** упорядоченная по возрастанию последовательность исходных чисел в выходном файле. Время работы программы: ~10 с (до 1 мин. для систем малой вычислительной мощности). 
* Максимально допустимый объём ОЗУ для хранения данных: 1 МБ. Очевидно, что размер входных данных гарантированно превысит 1МБ (это, к примеру, максимально допустимый объём стека вызовов, используемого для статических массивов). Требование по времени накладывает ограничение на количество чтений исходного файла.

Реализуйте задачу сортировки числового файла с заданными условиями. Добавьте в код возможность определения времени работы программы.

Для генерации случайного и уникального набора чисел используем `default_random_engine` и `set` (множество). 

```cpp
bool file_generation(int size) {
	if (size >= 10000000) return false;

	// Generator 
	set<int> numbers_set;
	default_random_engine u{};
	uniform_int_distribution<> d{};
	u.seed(random_device()()); // Analog srand
	while (numbers_set.size() < size)
		numbers_set.insert(d(u, uniform_int_distribution<>::param_type{ 0, RAND_MAX }));
	
	// Set to vector
	vector<int> numbers(numbers_set.begin(), numbers_set.end());
	shuffle(numbers.begin(), numbers.end(), u);
	
	// Create file
	ofstream out("input.txt");
	for (int num : numbers)
		out << num << endl;
	out.close();
	return true;
}
```

После генерации файла нам необходимо отсортировать его с помощью битового массива и засешь время работы программы (без учёта генирации файла).

```cpp
int main() {

	int size;

	cout << "Enter number of digits: ";
	cin >> size;
	if (!file_generation(size)) return 1;
	
	// Start timer
	auto start = high_resolution_clock::now();

	// Open files
	ifstream file_in("input.txt");
	ofstream file_out("output.txt");
	
	int tmp; 
	vector <unsigned char> data;

	// Unpack numbers
	while (file_in >> tmp) {
		if (tmp > data.size() * 8) data.resize(tmp / 8 + 1); // Resize vector
		data[tmp / 8] = data[tmp / 8] | (1 << (tmp % 8)); // Set Bit
	}

	// Pack numbers
	for (int i = 0; i < data.size(); i++)
	    for (int j = 0; j < 8; j++)
	        if ((1 << j) & data[i]) file_out << i * 8 + j << endl;

	// Stop timer and count duration
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	// Working time 
	cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
}
```

Принцип работы остался точно такой же, за исключением формата исходных данных. Так же добавился таймер, который засекает, за сколько выполнилась сортировка.

### Номер 3.б

Определите программно объём оперативной памяти, занимаемый битовым массивом.

Для этого добавим в программу добавим всего 1 строчку. Посколько в массиве хранится `unsigned char`, то каждый элемент занимает `1` байт.

```cpp
cout << "Size of binary array: \n\t" << data.size() << " bytes\n\t" << data.size() / 1024 << " kb";
```


## Альтернативные решения

* **Боронин Николай**
    * [1.а](./alt-BK/1a.cpp) 
    * [1.б](./alt-BK/1b.cpp) 
    * [1.в](./alt-BK/1c.cpp) 
    * [2.а](./alt-BK/2a.cpp) 
    * [2.б](./alt-BK/2b.cpp) 
    * [2.в](./alt-BK/2c.cpp) 
    * [3.a](./alt-BK/2c.cpp)