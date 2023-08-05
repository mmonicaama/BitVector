#include <iostream>
#include <string>
#include "BitVector.h"

BitVector::BitVector(int size) 
	: m_capacity((size + sizeof(unsigned int) * 8 - 1) / sizeof(unsigned int) * 8)
	, m_size(size)
{
	m_arr = new unsigned int[m_capacity];
	for (int i = 0; i < m_capacity; ++i) {
		m_arr[i] = 0;
	}
}

BitVector::BitVector(const BitVector& bits)
{
	m_size = bits.m_size;
	m_capacity = bits.m_capacity;
	m_arr = new unsigned int[m_capacity];
	for (int i = 0; i < m_capacity; ++i) {
		m_arr[i] = bits.m_arr[i];
	}
}

BitVector::~BitVector()
{
	delete[] m_arr;
}

int BitVector::size() const
{
	return m_size;
}

void BitVector::set(int idx)
{
	if (idx >= m_size) {
		std::cout << "Wrong index for set\n";
		return;
	}
	int byteIdx = idx / sizeof(unsigned int);
	int bitIdx = idx % sizeof(unsigned int);
	m_arr[byteIdx] |= (1 << bitIdx);
}

void BitVector::reset(int idx)
{
	if (idx >= m_size) {
		std::cout << "Wrong index for reset\n";
		return;
	}
	int byteIdx = idx / sizeof(unsigned int);
	int bitIdx = idx % sizeof(unsigned int);
	m_arr[byteIdx] &= ~(1 << bitIdx);
}

void BitVector::flip(int idx)
{
	if (idx >= m_size) {
		std::cout << "Wrong index for flip\n";
		return;
	}
	if (test(idx)) {
		reset(idx);
	}
	else {
		set(idx);
	}
}

void BitVector::resize(int size) 
{
	if (size <= 0) {
		std::cout << "Invalid size for resizing\n";
		return;
	}
	if (size == m_size) {
		return;
	}

	int newCapacity = m_capacity = (size + sizeof(unsigned int) * 8 - 1) / sizeof(unsigned int) * 8;
	unsigned int* tmp = new unsigned int[newCapacity];
	int copySize = std::min(newCapacity, m_capacity);

	for (int i = 0; i < copySize; ++i) {
		tmp[i] = m_arr[i];
	}
	for (int i = copySize; i < newCapacity; ++i) {
		tmp[i] = 0;
	}

	m_size = size;
	m_capacity = newCapacity;
	delete[] m_arr;
	m_arr = tmp;
	tmp = nullptr;
}

bool BitVector::test(int idx) const
{
	int byteIdx = idx / sizeof(unsigned int);
	int bitIdx = idx % sizeof(unsigned int);
	if (m_arr[byteIdx] & (1 << bitIdx)) {
		return true;
	}
	else {
		return false;
	}
}

void BitVector::swap(int idx1, int idx2)
{
	if (idx1 >= m_size || idx2 >= m_size) {
		std::cout << "Wrong index for swap\n";
		return;
	}
	unsigned int val1 = test(idx1);
	unsigned int val2 = test(idx2);
	if (val1) {
		set(idx2);
	}
	else {
		reset(idx2);
	}

	if (val2) {
		set(idx1);
	}
	else {
		reset(idx1);
	}
}

int BitVector::count() const
{
	int count{};
	for (int i = 0; i < m_size; ++i) {
		if (test(i)) {
			++count;
		}
	}
	return count;
}

bool BitVector::any() const
{
	for (int i = 0; i < m_size; ++i) {
		if (test(i)) {
			return true;
		}
	}
	return false;
}

bool BitVector::none() const
{
	for (int i = 0; i < m_size; ++i) {
		if (test(i)) {
			return false;
		}
	}
	return true;
}

bool BitVector::all() const
{
	for (int i = 0; i < m_size; ++i) {
		if (!test(i)) {
			return false;
		}
	}
	return true;
}

unsigned int BitVector::toInt() const
{
	unsigned int num = 0;
	for (int i = 0; i < m_size; ++i) {
		num += test(i) * (1u << i);
	}
	return num;
}

std::string BitVector::toString() const
{
	std::string str;
	for (int i = m_size - 1; i >= 0; --i) {
		if (test(i)) {
			str.push_back('1');
		}
		else {
			str.push_back('0');
		}
	}
	return str;
}

void BitVector::push_back(int bit)
{
	int newCapacity = (m_size + 1 + sizeof(unsigned int) * 8 - 1) / (sizeof(unsigned int) * 8);

	if (newCapacity > m_capacity) {
		unsigned int* tmp = new unsigned int[newCapacity];

		for (int i = 0; i < m_capacity; ++i) {
			tmp[i] = m_arr[i];
		}

		for (int i = m_capacity; i < newCapacity; ++i) {
			tmp[i] = 0;
		}

		delete[] m_arr;
		m_arr = tmp;
		m_capacity = newCapacity;
	}

	int lastByteIdx = (m_size) / sizeof(unsigned int);
	int lastBitIdx = (m_size) % sizeof(unsigned int);

	if (bit) {
		m_arr[lastByteIdx] |= (1 << lastBitIdx);
	}
	else {
		m_arr[lastByteIdx] &= ~(1 << lastBitIdx);
	}

	++m_size;
}

void BitVector::pop_back()
{
	if (m_size > 0) {
		--m_size;
		int lastByteIdx = m_size / sizeof(unsigned int);
		int lastBitIdx = m_size % sizeof(unsigned int);
		m_arr[lastByteIdx] &= ~(1 << lastBitIdx);
	}
	else {
		std::cout << "BitVector is empty, cannot pop_back\n";
	}
}

void BitVector::operator=(unsigned int num)
{
	unsigned int tmp = num;
	int size{};
	while (tmp != 0) {
		++size;
		tmp /= 2;
	}
	for (int i = 0; i < size; ++i) {
		if (num % 2 == 1) {
			set(i);
		}
		else {
			reset(i);
		}
		num /= 2;
	}
	for (int i = size; i < m_size; ++i) {
		reset(i);
	}
}

BitVector BitVector::operator&(const BitVector& bits)
{
	if (m_size != bits.m_size) {
		std::cout << "Sizes of bit vectors must be equal for operator AND\n";
		return BitVector(0);
	}

	BitVector result(m_size);

	for (int i = 0; i < m_capacity; ++i) {
		result.m_arr[i] = m_arr[i] & bits.m_arr[i];
	}

	return result;
}

BitVector BitVector::operator|(const BitVector& bits)
{
	if (m_size != bits.m_size) {
		std::cout << "Sizes of bit vectors must be equal for operator OR\n";
		return BitVector(0);
	}

	BitVector result(m_size);

	for (int i = 0; i < m_capacity; ++i) {
		result.m_arr[i] = m_arr[i] | bits.m_arr[i];
	}

	return result;
}

BitVector BitVector::operator^(const BitVector& bits)
{
	if (m_size != bits.m_size) {
		std::cout << "Sizes of bit vectors must be equal for operator XOR\n";
		return BitVector(0);
	}

	BitVector result(m_size);

	for (int i = 0; i < m_capacity; ++i) {
		result.m_arr[i] = m_arr[i] ^ bits.m_arr[i];
	}

	return result;
}

BitVector BitVector::operator~()
{
	BitVector result(m_size);

	for (int i = 0; i < m_capacity; ++i) {
		result.m_arr[i] = ~m_arr[i];
	}

	return result;
}