#include <iostream>
#include <vector>
#include <math.h>
#include <string>

#define STRONG 0
#define SEMISTRONG 1
#define WEAK 2

#define BETA (11.0/3.0)
const int MAX_ALPHABET = 15;

class ParichVector {
public:
	ParichVector(std::string w);
	std::string repr();

	friend bool operator==(const ParichVector &p, const ParichVector &q);
	friend bool operator!=(const ParichVector &p, const ParichVector &q);
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
bool operator!=(const ParichVector &p, const ParichVector &q)
{
	return !(p == q);
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


// Utils
std::string to_letter(int i) { return std::to_string('a' + i); }

//Algorithm

// Checks whether word w is a strong (semi-strong, weak)

// Checks whether len(w) satisfies Lemma 4.2 [1]
// w_len = length of w, root_len = length of r, defenition is type of Abelian period
// one of {STRONG, SEMISTRONG, WEAK}
bool satisfied_lemma_4_2(int w_len, int root_len, char defenition)
{
	if (defenition == STRONG)
	{
		if (ceil(root_len * BETA) <= w_len && w_len <= root_len * ceil(BETA))
			return true;
	}
	return false;

}

// Checks whether word w has Abelian power with the given root.
bool isAbelian(std::string w, std::string root)
{
	if (w == root)
		return false;

	if (!satisfied_lemma_4_2(w.length(), root.length(), STRONG))
		return false;

	for (int i = 0; i < w.length()/root.length(); ++i)
	{
		if (ParichVector(w.substr(0, root.length())) != ParichVector(w.substr(i*root.length(), root.length())))
			return false;
	}

	int tail_len = w.length() % root.length();
	if (tail_len == 0)
		return true;
	std::string tail = w.substr(w.length()-tail_len, tail_len);// [-tail_len:]

	if (ParichVector(tail) == ParichVector(w.substr(0, tail_len)))
		return true;

	return false;
}

void test_ParichVector()
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
}
void test_isAbelian()
{
	std::cout << (isAbelian("abbbabbbaab", "abb") ? "Correct" : "failed!") << "\n"
		<< (isAbelian("aabaabaababa", "aab") ? "Correct" : "failed!") << "\n"
		<< (isAbelian("aabaabbaaaba", "aab") ? "Correct" : "failed!") << "\n";
}

int main()
{
	system("PAUSE");
	return 0;
}
