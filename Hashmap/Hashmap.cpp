// Hashmap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "hashmap.h"

int main() {
	HashMap<int, std::string> hm;
	
	hm.put(100, "key");
	
	std::cout << hm[100] << std::endl;

	hm.remove(100);

	std::cout << hm[100] << std::endl;
	/*hm.put("Alex", 230222);
	hm.put("Monica", 203100);
	hm.put("Rebecca", 100000);

	std::cout << hm["Alex"] << std::endl;*/

	

    std::cout << "Hello World!\n"; 
}

 