#pragma once
#include <set>
#include <queue>
#include <string>
#include "ParichVector.h"
#include "grate/dfa.h"
#include "grate/eigenvalue.h"
#pragma comment (lib, "third_party/grate_core.lib")
#pragma comment (lib, "third_party/grate_binary_patterns.lib")
#pragma comment (lib, "third_party/grate_util.lib")


class AbelianLexminTrie
{
public:
	void add_initial(std::set<std::string> initial);
	growth_rate::LexminTrie* construct_lex_min_trie(int iterations, bool verbose);
	AbelianLexminTrie(int alphabet_len, float beta);
	
	static const char NOTABELIAN = 0;
	static const char STRONG = 1;
	static const char SEMISTRONG = 2;
	static const char WEAK = 3;

	bool satisfied_lemma_4_2(int w_len, int root_len, char defenition);
	char isAbelian(std::string w, std::string root);
	bool has_no_forbidden_proper_suffixes(std::string w);
private:
	growth_rate::LexminTrie* trie; //std::set<std::string> trie;
	float BETA;
	int alphabet_len;

	void build(std::string w, std::string r, ParichVector p);
	void iterate(std::queue<std::pair<std::string, int>> Q, int R);

	std::set<std::string> correct_trie;
};
