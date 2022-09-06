#include <set>
#include <iostream>
#include <bitset>
#include <vector>
#include <ctime>
#include <fstream>
#include <cmath>
#include <random>
#include <cstdlib> 
#include <stdio.h>
#include <algorithm>
#include <chrono>
#include <windows.h>

#define RAND_MAX 10000000 //2147483647

using namespace std;
using namespace std::chrono;

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

	cout << "Size of binary array: \n\t" << data.size() << " bytes\n\t" << data.size() / 1024 << " kb";
}