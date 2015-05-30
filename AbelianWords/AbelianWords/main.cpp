#include <iostream>
#include <vector>
#include <math.h>
#include <string>

const int MAX_ALPHABET = 15;

class ParichVector {
public:
	ParichVector(std::string w);

	friend bool operator==(const ParichVector &p, const ParichVector &q);
	friend ParichVector operator+(const ParichVector &p, const ParichVector &q);
	friend ParichVector operator-(const ParichVector &p, const ParichVector &q);
	int operator[](int i) const { return vector[i]; }
	int & operator[](int i)     { return vector[i]; }
	// <=
	// ToString

private:
	int vector[MAX_ALPHABET];
};

ParichVector::ParichVector(std::string w)
{
	for (int i = 0; i < MAX_ALPHABET; ++i)
		vector[i] = 0;
	for (int i = 0; i < w.length(); ++i)
		++vector[w[i]];
}

bool operator==(const ParichVector &p, const ParichVector &q)
{
	for (int i = 0; i < MAX_ALPHABET; ++i)
	if (p[i] != q[i])
		return false;
	return true;
}

ParichVector operator+(const ParichVector &p, const ParichVector &q)
{
	ParichVector sum = ParichVector("");
	for (int i = 0; i < MAX_ALPHABET; ++i)
		sum[i] = p[i] + q[i];
	return sum;
}

ParichVector operator-(const ParichVector &p, const ParichVector &q)
{
	ParichVector sum = ParichVector("");
	for (int i = 0; i < MAX_ALPHABET; ++i)
		sum[i] = p[i] - q[i];
	return sum;
}


int main()
{
	
	return 0;
}
