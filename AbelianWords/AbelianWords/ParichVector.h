#pragma once
#include <string>
#include "const.h"

class ParichVector {
public:
	ParichVector(std::string w);
	std::string repr();

	friend bool operator==(const ParichVector &p, const ParichVector &q);
	friend bool operator!=(const ParichVector &p, const ParichVector &q);
	friend bool operator<=(const ParichVector &p, const ParichVector &q);
	friend ParichVector operator+(const ParichVector &p, const ParichVector &q);
	friend ParichVector operator-(const ParichVector &p, const ParichVector &q);
	int operator[](int i) const { return vector[i-'a']; }
	int & operator[](int i)     { return vector[i-'a']; }

	static int alphabet_len;

private:
	int vector[MAX_ALPHABET];
};
