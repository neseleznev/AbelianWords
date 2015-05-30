#include <iostream>
#include <vector>
#include <math.h>
#include <string>

const int MAX_ALPHABET = 15;

class ParichVector {
public:
	ParichVector(std::string w);
	std::string repr();

	friend bool operator==(const ParichVector &p, const ParichVector &q);
	friend bool operator<=(const ParichVector &p, const ParichVector &q);
	friend ParichVector operator+(const ParichVector &p, const ParichVector &q);
	friend ParichVector operator-(const ParichVector &p, const ParichVector &q);
	int operator[](int i) const { return vector[i]; }
	int & operator[](int i)     { return vector[i]; }

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

bool operator<=(const ParichVector &p, const ParichVector &q)
{
	for (int i = 0; i < MAX_ALPHABET; ++i)
	if (p[i] > q[i])
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

std::string ParichVector::repr()
{
	std::string s = "(";
	for (int i = 0; i < MAX_ALPHABET - 1; ++i)
		s.append(std::to_string(vector[i]) + ", ");
	s.insert(s.end() - 1, ')');
	return s;
}


int main()
{
	std::cout << "ParichVector tests:\ns = 'aba'\n";
	std::string s = "   ";
	s[0] = 0; s[1] = 1;	s[2] = 0;
	ParichVector p = ParichVector(s);

	std::cout << "p(s) \t= " << p.repr() << "\n";
	p = p + p;
	std::cout << "p+p \t= " << p.repr() << "\n";
	std::cout << ((p == p) ? "p == p" : "p != p") << "\n";
	std::cout << ((p <= p) ? "p <= p" : "p > p") << "\n";
	p = p - p;
	std::cout << "p-p \t= " << p.repr() << "\n";
	
	system("PAUSE");
	return 0;
}
