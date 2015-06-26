#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <math.h>
#include <string>
#include <algorithm>
#include <time.h>

#include "AbelianLexminTrie.h"
#include "const.h"


void test_ParichVector()
{
	std::cout << "ParichVector tests:\ns = 'aba'\n";
	std::string s = "aba";
	ParichVector p = ParichVector(s);

	std::cout << "p(s) \t= " << p.repr() << "\n";
	p = p + p;
	std::cout << "p+p \t= " << p.repr() << "\n";
	std::cout << ((p == p) ? "p == p" : "p != p") << "\n";
	std::cout << ((p <= p) ? "p <= p" : "p > p") << "\n";
	p = p - p;
	std::cout << "p-p \t= " << p.repr() << "\n";
}

void test_satisfied_lemma_4_2()
{
	std::cout << "satisfied_lemma_4_2 tests:\ns = 'aba'\n";
	AbelianLexminTrie ALT = AbelianLexminTrie(2, (11.0 / 3.0));

	std::vector<std::string> words = std::vector<std::string>{ "aabaabaabaa" };
	std::vector<std::string> roots = std::vector<std::string>{ "aab" };
	for (size_t i = 0; i < words.size(); ++i)
		std::cout << words[i] << ", " << roots[i] << ": " <<
		(ALT.satisfied_lemma_4_2(words[i].length(), roots[i].length(),
		AbelianLexminTrie::STRONG) ? "True" : "False") << "\n";
}

void test_isAbelian()
{
	std::cout << "isAbelian tests:\n";
	AbelianLexminTrie ALT = AbelianLexminTrie(2, (11.0 / 3.0));
	
	std::cout << (ALT.isAbelian("abbbabbbaab", "abb") ? "Correct" : "failed!") << "\n"
		<< (ALT.isAbelian("aabaabaababa", "aab") ? "Correct" : "failed!") << "\n"
		<< (ALT.isAbelian("aabaabbaaaba", "aab") ? "Correct" : "failed!") << "\n";
}

void test_has_no_forbidden_suffixes()
{
	std::cout << "has_no_proper_suffixes tests:\n";
	AbelianLexminTrie ALT = AbelianLexminTrie(2, (11.0 / 3.0));

	std::cout << (ALT.has_no_forbidden_proper_suffixes("ababababab") ? "failed" : "Correct") << "\n"

		<< (ALT.has_no_forbidden_proper_suffixes("aaaa") ? "Correct" : "failed") << "\n"
		<< (ALT.has_no_forbidden_proper_suffixes("bbbb") ? "Correct" : "failed") << "\n"

		<< (ALT.has_no_forbidden_proper_suffixes("aaaaaaabbbabbbaab") ? "failed" : "Correct") << "\n"
		<< (ALT.has_no_forbidden_proper_suffixes("aaabbbabbbaab") ? "failed" : "Correct") << "\n";
}


int main()
{
	test_ParichVector();
	test_satisfied_lemma_4_2();
	test_isAbelian();
	test_has_no_forbidden_suffixes();

	ParichVector::alphabet_len = 2;
	AbelianLexminTrie ALT = AbelianLexminTrie(2, (float)(11.0/3.0));
	ALT.add_initial(std::set<std::string>{"aaaa"});
	growth_rate::LexminTrie *trie = ALT.construct_lex_min_trie(10, true);

	growth_rate::LexminDFA *dfa = new growth_rate::LexminDFA(trie);
	delete trie;

	size_t iterations_used;
	double result = growth_rate::EigenvalueCalculator::get_max_eigenvalue(dfa,
		growth_rate::EigenvalueOptions(), &iterations_used);
	std::cout << "\nGrowth rate = " << result;
	system("PAUSE");
	return 0;
}
