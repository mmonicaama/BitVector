#include <iostream>
#include <string>
#include "BitVector.h"

int main()
{
	BitVector bits1(64);
	bits1 = 2;
	BitVector bits2(64);
	bits2 = 1;
	bits2.push_back(1);
	
	std::string str;
	str = bits2.toString();
	std::cout << str << std::endl;

	std::cout << "XOR : " << (bits1 ^ bits2).toInt() << std::endl;
	std::cout << "Size : " << bits1.size() << std::endl;
	std::cout << "Bitset : " << bits1.toInt() << std::endl;
	std::cout << "Size : " << bits2.size() << std::endl;
	std::cout << "Bitset : " << bits2.toInt() << std::endl;
	return 0;
}