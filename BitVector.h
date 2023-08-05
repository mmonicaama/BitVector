#pragma once
#include <string>

class BitVector
{
public:
	BitVector(int); // param constructor
	BitVector(const BitVector&); // copy constructor
	~BitVector();
	int size() const;
	void set(int);
	void reset(int);
	void flip(int);
	void resize(int size);
	bool test(int) const;
	void swap(int, int);
	int count() const; // Returns the number of set bits(1s)
	bool any() const; //  Returns true if any bit is set (1), false otherwise
	bool none() const; // Returns true if none of the bits are set (all 0), false otherwise
	bool all() const; // Returns true if all bits are set (all 1), false otherwise.
	unsigned int toInt() const;
	std::string toString() const;
	void push_back(int);
	void pop_back();

public:
	void operator=(unsigned int);
	BitVector operator&(const BitVector&);
	BitVector operator|(const BitVector&);
	BitVector operator^(const BitVector&);
	BitVector operator~();

private:
	unsigned int* m_arr;
	int m_size;
	int m_capacity;
};