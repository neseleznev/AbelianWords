#include "ParichVector.h"


int ParichVector::alphabet_len;

ParichVector::ParichVector(std::string w)
{
	for (int i = 0; i < alphabet_len; ++i)
		vector[i] = 0;
	for (size_t i = 0; i < w.length(); ++i)
		++vector[w[i] - 'a'];
}

bool operator==(const ParichVector &p, const ParichVector &q)
{
	for (int i = 0; i < p.alphabet_len; ++i)
	if (p[i] != q[i])
		return false;
	return true;
}
bool operator!=(const ParichVector &p, const ParichVector &q)
{
	return !(p == q);
}

bool operator<=(const ParichVector &p, const ParichVector &q)
{
	for (int i = 0; i < p.alphabet_len; ++i)
	if (p[i] > q[i])
		return false;
	return true;
}

ParichVector operator+(const ParichVector &p, const ParichVector &q)
{
	ParichVector sum = ParichVector("");
	for (int i = 0; i < p.alphabet_len; ++i)
		sum[i] = p[i] + q[i];
	return sum;
}

ParichVector operator-(const ParichVector &p, const ParichVector &q)
{
	ParichVector sum = ParichVector("");
	for (int i = 0; i < p.alphabet_len; ++i)
		sum[i] = p[i] - q[i];
	return sum;
}

std::string ParichVector::repr()
{
	std::string s = "(";
	for (int i = 0; i < alphabet_len - 1; ++i)
		s.append(std::to_string(vector[i]) + ", ");
	s.insert(s.end() - 1, ')');
	return s;
}
