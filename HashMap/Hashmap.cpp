// Hashmap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include "hashmap.h"

const size_t tableSize = 10;


struct A {
	std::string text;
	u64 num = 0;
	friend bool operator!=(const A &a, const A &b) {
		return !(a == b);
	}
	friend bool operator==(const A& a, const A& b) {
		return (a.text == b.text && a.num == b.num);
	}
};

int main() {

	HashMap<A, int, tableSize> hm;
	A test{ "test", 5 };
	hm.put(test, 3);
	std::cout << hm[test] << std::endl;


	HashMap<std::string, int, tableSize> hmap;

	std::ifstream file("data/surnames-key.txt");

	int value;
	std::string key;
	std::string line;
	clock_t start = 0, end = 0;

	if (file.is_open()) {
		start = clock();
		while (std::getline(file, line)) {
			std::istringstream ss(line);
			if (ss >> key && ss >> value) {
				hmap.put(key, value);
			}
		}
		end = clock();
		file.close();
	}

	
	hmap.showTableFilling();
	std::cout << "Time: " << (double)((u64)end - (u64)start) / CLOCKS_PER_SEC << std::endl;

	system("PAUSE");
}

 