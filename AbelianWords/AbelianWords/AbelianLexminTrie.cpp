#include "AbelianLexminTrie.h"
#include <iostream>
#include <time.h>

AbelianLexminTrie::AbelianLexminTrie(int alphabet_len, float beta)
    :   alphabet_len(alphabet_len),
        BETA(beta) {
	trie = new growth_rate::LexminTrie((uint32_t)10000, (uint8_t)alphabet_len);
	//correct_trie = std::set<std::string>{ to_my_str("aaaa"), to_my_str("aaaaaaaa"),
	//	to_my_str("abababab"), to_my_str("abababba"), to_my_str("ababbaab"), to_my_str("ababbaba"), to_my_str("abbaabab"), to_my_str("abbaabba"), to_my_str("abbabaab"), to_my_str("abbababa"),
	//	// 11 - aab aab aab aa
	//	to_my_str("aabaabaabaa"), to_my_str("aabaababaaa"), to_my_str("aabaabbaaaa"), to_my_str("aababaaabaa"), to_my_str("aababaabaaa"), to_my_str("aabababaaaa"), to_my_str("aabbaaaabaa"), to_my_str("aabbaaabaaa"), to_my_str("aabbaabaaaa"),
	//	// 11 - aba aba aba ab
	//	to_my_str("abaabaaabab"), to_my_str("abaabaabaab"), to_my_str("abaababaaab"), to_my_str("abaaabaabab"), to_my_str("abaaababaab"), to_my_str("abaaabbaaab"), to_my_str("ababaaaabab"), to_my_str("ababaaabaab"), to_my_str("ababaabaaab"), to_my_str("abaabaaabba"), to_my_str("abaabaababa"), to_my_str("abaababaaba"), to_my_str("abaaabaabba"), to_my_str("abaaabababa"), to_my_str("abaaabbaaba"), to_my_str("ababaaaabba"), to_my_str("ababaaababa"), to_my_str("ababaabaaba"),
	//	// 11 - abb abb abb ab
	//	to_my_str("abbabbabbab"), to_my_str("abbabbbabab"), to_my_str("abbabbbbaab"), to_my_str("abbbababbab"), to_my_str("abbbabbabab"), to_my_str("abbbabbbaab"), to_my_str("abbbbaabbab"), to_my_str("abbbbababab"), to_my_str("abbbbabbaab"), to_my_str("abbabbabbba"), to_my_str("abbabbbabba"), to_my_str("abbabbbbaba"), to_my_str("abbbababbba"), to_my_str("abbbabbabba"), to_my_str("abbbabbbaba"), to_my_str("abbbbaabbba"), to_my_str("abbbbababba"), to_my_str("abbbbabbaba"),
	//	// 12 - aab aab aab aba
	//	to_my_str("aabaabbaaaba"), to_my_str("aabababaaaba"), to_my_str("aabbaaaababa"), to_my_str("aabbaaabaaba"), to_my_str("aabbaabaaaba"),
	//	// 12 - aab aab aab baa
	//	to_my_str("aabaabaabbaa"), to_my_str("aababaaabbaa"), to_my_str("aabbaaaabbaa"), to_my_str("aabbaaababaa"), to_my_str("aabbaabaabaa"),
	//	// 12 - aba aab aab aab
	//	to_my_str("abaaabbaaaab"), to_my_str("abaababaaaab"), to_my_str("ababaaaabaab"), to_my_str("ababaaabaaab"), to_my_str("ababaabaaaab"),
	//	// 12 - abb aab aab aab
	//	to_my_str("abbabbabbbba"), to_my_str("abbabbbabbba"), to_my_str("abbabbbbabba"), to_my_str("abbbababbbba"), to_my_str("abbbabbabbba"), to_my_str("abbbabbbabba"), to_my_str("abbbbaabbbba"), to_my_str("abbbbababbba"), to_my_str("abbbbabbabba"),
	//};
}

void AbelianLexminTrie::add_initial(std::set<std::string> initial)
{
	for (std::set<std::string>::iterator it = initial.begin(); it != initial.end(); ++it)
	{
		trie->add_lexmin_word(growth_rate::Word((*it).c_str())); //trie.insert(to_my_str(*it));
	}
}

growth_rate::LexminTrie* AbelianLexminTrie::construct_lex_min_trie(int iterations, bool verbose = false)
{
	// all possible roots of lexmin words in an auxiliary queue Q
	std::queue<std::pair<std::string, int>> Q = std::queue<std::pair<std::string, int>>();
	time_t start_time;
	std::vector<int> tries_len = std::vector<int>();

	for (int R = 1; R <= iterations; ++R)
	{
		if (verbose)
		{
			std::cout << "\n\nIterate, R=" << R;
			start_time = clock();
		}

		iterate(Q, R);

		/*if (verbose)
		{
		tries_len.push_back(trie.size());
		std::cout << "\n\t|trie| = " << tries_len[R - 1] << "\n\tcomputed in " << float(clock() - start_time) / 1000.0 << " seconds";
		if (R > 1)
		std::cout << "\n\ttrie[" << R << "] / trie[" << R + 1 << "] = " << (float(tries_len[R - 1]) / float(tries_len[R - 2]));
		}

		if (verbose && R == iterations)
		{
		std::cout << "\n\nTrie - Correct\n";
		int trie_minus_correct = 0;
		for (std::set<std::string>::iterator it = trie.begin(); it != trie.end(); ++it)
		{
		if ((*it).length() <= 12)
		{
		if (correct_trie.find(*it) == correct_trie.end())
		{
		std::cout << "<" << *it << ">\n";
		++trie_minus_correct;
		}
		}
		}
		std::cout << "Overall: " << trie_minus_correct << "\n";

		std::cout << "\nCorrect - Trie\n";

		int correct_minus_trie = 0;
		for (std::set<std::string>::iterator it = correct_trie.begin(); it != correct_trie.end(); ++it)
		{
		if ((*it).length() <= 12)
		{
		if (trie.find(*it) == trie.end())
		{
		std::cout << "<" << *it << ">\n";
		++correct_minus_trie;
		}
		}
		}
		std::cout << "Overall: " << correct_minus_trie << "\n";
		}*/
	}
	return trie;
}

// Checks whether len(w) satisfies Lemma 4.2 [1]
// w_len = length of w, root_len = length of r, defenition is type of Abelian period
// one of {STRONG, SEMISTRONG, WEAK}
bool AbelianLexminTrie::satisfied_lemma_4_2(int w_len, int root_len, char defenition)
{
	if (defenition == STRONG)
	{
		if (ceil(root_len * BETA) <= w_len && w_len <= root_len * ceil(BETA))
			return true;
	}
	return false;
}

// Checks whether word w has Abelian power with the given root.
char AbelianLexminTrie::isAbelian(std::string w, std::string root)
{
	if (w == root)
		return NOTABELIAN;

	if (!satisfied_lemma_4_2(w.length(), root.length(), STRONG))
		return NOTABELIAN;

	for (size_t i = 0; i < w.length() / root.length(); ++i)
	{
		if (ParichVector(w.substr(0, root.length())) != ParichVector(w.substr(i*root.length(), root.length())))
			return NOTABELIAN;
	}

	int tail_len = w.length() % root.length();
	if (tail_len == 0)
		return STRONG;
	std::string tail = w.substr(w.length() - tail_len, tail_len);// [-tail_len:]

	if (ParichVector(tail) == ParichVector(w.substr(0, tail_len)))
		return STRONG;

	return NOTABELIAN;
}

bool AbelianLexminTrie::has_no_forbidden_proper_suffixes(std::string w)
{
	double intpart;
	// BETA is an integer
	if (modf(BETA, &intpart) == 0.0)
	{
		std::reverse(w.begin(), w.end());
		for (size_t pref_len = 1; pref_len < w.length(); ++pref_len)
		if (trie->accepts_word(w.substr(0, pref_len).c_str(), growth_rate::Forward)) //trie.find(w.substr(0, pref_len)) != trie.end())
			return false;
		return true;
	}
	// BETA is fraction
	for (size_t suff_len = 1; suff_len < w.length(); ++suff_len)
	for (size_t root_len = 1; root_len < (w.length() - suff_len + 1) / (int)BETA; ++root_len)
	if (isAbelian(w.substr(suff_len, w.length() - suff_len), w.substr(suff_len, root_len)))
		return false;
	return true;
}

void AbelianLexminTrie::build(std::string w, std::string r, ParichVector p)
{
	// fout.write("\t\t" + ("_" * 30) + "\n")
	// fout.write("\t\t|BUILD(w=" + w + ", r=" + r + ", p=" + str(p) + "):\n")
	if (isAbelian(w, r))
	{
		// fout.write("\t\t |\t(" + w + ", " + r + ") is_abelian\n")
		std::cout << "<" << w << ">" << "\n";
		if (!w.empty() && satisfied_lemma_4_2(w.length(), r.length(), STRONG))
		{
			// fout.write("\t\t |\t\t|w|, |r| satisfied lemma 4.2; Adding to trie\n")
			trie->add_lexmin_word(growth_rate::Word(w.c_str())); //trie.insert(w);
		}
		// print("To trie: " + w)
		// fout.write("\t\t |\t\t|w|, |r| NOT satisfied lemma 4.2\n")
		// fout.write("\t\t |\treturn (from BUILD)\n")
		// fout.write("\t\t " + ("-" * 30) + "\n")
		return;
	}
	// if len(w) equals the upper bound from Lemma 4.2
	if ((isAbelian(w, r) == STRONG && w.length() == r.length() * (int)ceil(BETA)))
		// fout.write("\t\t |\t|w| equals the upper bound from Lemma 4.2\n")
		// fout.write("\t\t |\treturn (from BUILD)\n")
		// fout.write("\t\t " + ("-" * 30) + "\n")
		return;

	if (w.length() % r.length() == 0)
		// fout.write("\t\t |\t|w| mod |r| = 0\n")
		p = ParichVector(r);
	// fout.write("\t\t |\tp = Parich_vector(r) = " + str(p) + "\n")

	// fout.write("\t\t |\tfor each c in ALPHABET:\n")
	for (char c = 'a'; c < 'a' + alphabet_len; ++c)
	{
		// fout.write("\t\t |\t\tc=" + str(c) + "\n")
		if (p[c] > 0)
		{
			// fout.write("\t\t |\t\tp[" + c + "] > 0\n")
			// fout.write("\t\t |\t\t\tu = w + c = " + w + c + "\n")
			std::string u = w;
			u += c;
			// fout.write("\t\t |\t\t\tq = p = " + str(p) + "\n")
			ParichVector q = p;
			// fout.write("\t\t |\t\t\tq[" + c + "] -= 1; q = " + str(q) + "\n")
			q[c] -= 1;
			if (has_no_forbidden_proper_suffixes(u))
			{
				// fout.write("\t\t |\t\t\tu (" + u + ") has_no_forbidden_proper_suffixes\n")
				// fout.write("\t\t |\t\t\t\tbuild(u=" + u + ", r=" + r + ", q=" + str(q) + ")\n")
				// fout.write("\t\t " + ("-" * 30) + "\n")
				build(u, r, q);
			}
			//fout.write("\t\t " + ("-" * 30) + "\n")
		}
	}
}

void AbelianLexminTrie::iterate(std::queue<std::pair<std::string, int>> Q, int R)
{
	// fout.write("" + ("_" * 30) + "\n")
	// fout.write("ITERATE(Q=" + str(Q) + ", R=" + str(R) + "):\n")
	Q.push(std::pair<std::string, int>(std::string("a"), 1));
	// fout.write("\twhile Q:\n")
	std::pair<std::string, int> element;
	while (!Q.empty())
	{
		element = Q.front();
		Q.pop();
		std::string r = element.first; int t = element.second;
		// fout.write("\t\t(" + r + ", " + str(t) + ") pop form Q\n")
		build(r, r, ParichVector(r));
		if ((int)r.length() < R)
		{
			// fout.write("\t\t|r| (" + str(len(r)) + ") < R (" + str(R) + ")\n")
			// fout.write("\t\tfor each c in [0; t]:\n")
			for (char c = 'a'; c < 'a' + t + 1; ++c)
			{
				// fout.write("\t\t\tc=" + to_sym(c) + "\n")
				if (has_no_forbidden_proper_suffixes('a' + r + c))
				{
					// fout.write("\t\t\t\t rc (" + r + to_sym(c) + ") has_no_forbidden_proper_suffixes\n")
					// fout.write("\t\t\t\tQ.append(" + r + to_sym(c) + ", " + str(t) + ")\n")
					Q.push(std::pair<std::string, int>(r + c, t));
				}
			}
			if (t + 1 < alphabet_len)
			{
				// fout.write("\t\tif t+1 (" + str(t + 1) + ") < K:\n")
				// fout.write("\t\t\tQ.append(" + r + to_sym(t + 1) + ", " + str(t + 1) + ")\n")
				Q.push(std::pair<std::string, int>(r + (char)('a' + t + 1), t + 1));
			}
		}
	}
}
