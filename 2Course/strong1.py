#!/usr/bin/env python3
# -*- coding: cp1251 -*-
import Queue, sys, copy
import math, time

flag = False

K = 2
beta = 11.0 / 3.0
letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']

correct_trie = {
# 4 - aaaa
	"aaaa",

# 8 - aaaaaaaa
	"aaaaaaaa",

# 8 - ab ab ab ab
	"abababab",  #?
	"abababba",
	"ababbaab",
	"ababbaba",
		"abbaabab",
		"abbaabba",
		"abbabaab",
		"abbababa",

# 11 - aab aab aab aa
	"aabaabaabaa",
	"aabaababaaa",
	"aabaabbaaaa",
		"aababaaabaa",
		"aababaabaaa",
		"aabababaaaa",
			"aabbaaaabaa",
			"aabbaaabaaa",
			"aabbaabaaaa",

# 11 - aba aba aba ab
	"abaabaaabab",
	"abaabaabaab",
	"abaababaaab",
		"abaaabaabab",
		"abaaababaab",
		"abaaabbaaab",
			"ababaaaabab",
			"ababaaabaab",
			"ababaabaaab",
	"abaabaaabba",
	"abaabaababa",
	"abaababaaba",
		"abaaabaabba",
		"abaaabababa",
		"abaaabbaaba",
			"ababaaaabba",
			"ababaaababa",
			"ababaabaaba",

# 11 - abb abb abb ab
	"abbabbabbab",
	"abbabbbabab",
	"abbabbbbaab",
		"abbbababbab",
		"abbbabbabab",
		"abbbabbbaab",
			"abbbbaabbab",
			"abbbbababab",
			"abbbbabbaab",
	"abbabbabbba",
	"abbabbbabba",
	"abbabbbbaba",
		"abbbababbba",
		"abbbabbabba",
		"abbbabbbaba",
			"abbbbaabbba",
			"abbbbababba",
			"abbbbabbaba",

# 12 - aab aab aab aba
	# "aabaabaababa",
	# "aabaababaaba",
	"aabaabbaaaba",
		# "aababaaababa",
		# "aababaabaaba",
		"aabababaaaba",
			"aabbaaaababa",
			"aabbaaabaaba",
			"aabbaabaaaba",

# 12 - aab aab aab baa
	"aabaabaabbaa",
	# "aabaabababaa",
	# "aabaabbaabaa",
		"aababaaabbaa",
		# "aababaababaa",
		# "aabababaabaa",
			"aabbaaaabbaa",
			"aabbaaababaa",
			"aabbaabaabaa",

# 12 - aba aab aab aab
	# "abaaabaabaab",
	# "abaaababaaab",
	"abaaabbaaaab",
		# "abaabaaabaab",
		# "abaabaabaaab",
		"abaababaaaab",
			"ababaaaabaab",
			"ababaaabaaab",
			"ababaabaaaab",

# 12 - abb aab aab aab
	"abbabbabbbba",
	"abbabbbabbba",
	"abbabbbbabba",
		"abbbababbbba",
		"abbbabbabbba",
		"abbbabbbabba",
			"abbbbaabbbba",
			"abbbbababbba",
			"abbbbabbabba",
}
trie = set(["aaaa"])


fout = open("out.txt", "w")

def to_sym(i):
	return letters[i]

class MyException(Exception):
	def __init__(self, value):
		self.value = value
	def __str__(self):
		return repr(self.value)


class Parich_vector:

	def __init__(self, w):
		self.vector = dict()
		for letter in letters[:K]:
			self.vector[letter] = 0
		for letter in w:
			if not (letter in letters[:K]):
				raise MyException("wrong alphabet of word \"" + str(w) + "\"")
			self.vector[letter] += 1

	def plus(self, v):
		if self.vector.keys() != v.get_vector().keys():
			raise MyException("wrong alphabet of word \"" + str(v) + "\"")

		for l in letters[:K]:
			self[l] += v[l]

	def minus(self, v):
		if self.vector.keys() != v.get_vector().keys():
			raise MyException("wrong alphabet of word \"" + str(v) + "\"")

		for l in letters[:K]:
			self[l] -= v[l]

	def __getitem__(self, ind):
		return self.vector[ind]

	def __setitem__(self, ind, value):
		self.vector[ind] = value

	def __eq__(self, v):
		return self.vector.items() == v.vector.items()

	def __le__(self, v):
		if self.vector.keys() != v.get_vector().keys():
			raise MyException("wrong alphabet of word \"" + str(w) + "\"")

		for key in letters[:K]:
			if self[key] > v[key]:
				return False
		return True

	def __str__(self):
		s = "("
		for l in letters[:K - 1]:
			s += str(self[l]) + ", "
		s += str(self[letters[K - 1]])
		return s + ")"


def is_abelian(w, r):
	'''Checks whether w is a strong
	Abelian power with the root r.'''
	if w == r:
		return False

	if not satisfied_lemma_4_2(len(w), len(r), "Strong"):
		return False

	for i in range(0, len(w) // len(r)):
		if not Parich_vector(w[0:len(r)]) == Parich_vector(w[i*len(r) : (i+1)*len(r)]):
			return False

	tail_len = len(w) % len(r)
	tail = w[-tail_len:]
	if tail_len == 0:
		return True

	if Parich_vector(tail) == Parich_vector(w[0:tail_len]):
		return True

	return False


def satisfied_lemma_4_2(w, r, w_type):
	''' Checks whether len(w) satisfies Lemma 4.2
		w = len(w), r = len(r), w_type is type of Abelian period
	'''
	if w_type == "Strong":
		if int(math.ceil(r * beta)) <= w <= int(r * math.ceil(beta)):
			return True
	return False


def has_no_forbidden_proper_suffixes(w):
	if type(beta) == type(1):  # beta is an integer
		print("______________________________")
		w = w[::-1]
		for pref_len in range(1, len(w)):
			# print("\t(int) " + w[:pref_len])
			if w[:pref_len] in trie:
				return False
		return True

	# beta is not an integer
	for suff_len in range(1, len(w)):
		for root_len in range(1, int((len(w) - suff_len + 1) / math.floor(beta))):
			# print("\t" + w[suff_len:] + " " + w[suff_len : suff_len+root_len])
			if is_abelian(w[suff_len:], w[suff_len : suff_len+root_len]):
				return False
	return True


def build(w, r, p):
	# fout.write("\t\t" + ("_" * 30) + "\n")
	# fout.write("\t\t|BUILD(w=" + w + ", r=" + r + ", p=" + str(p) + "):\n")
	if is_abelian(w, r):
		# fout.write("\t\t |\t(" + w + ", " + r + ") is_abelian\n")
		if satisfied_lemma_4_2(len(w), len(r), "Strong"):
			# fout.write("\t\t |\t\t|w|, |r| satisfied lemma 4.2; Adding to trie\n")
			trie.add(w)
			# print("To trie: " + w)
		# fout.write("\t\t |\t\t|w|, |r| NOT satisfied lemma 4.2\n")
		# fout.write("\t\t |\treturn (from BUILD)\n")
		# fout.write("\t\t " + ("-" * 30) + "\n")
		return

	# if len(w) equals the upper bound from Lemma 4.2
	if is_abelian(w, r) == "Strong" and len(w) == len(r) * int(math.ceil( beta )):
		# fout.write("\t\t |\t|w| equals the upper bound from Lemma 4.2\n")
		# fout.write("\t\t |\treturn (from BUILD)\n")
		# fout.write("\t\t " + ("-" * 30) + "\n")
		return

	if len(w) % len(r) == 0:
		# fout.write("\t\t |\t|w| mod |r| = 0\n")
		p = Parich_vector(r)
		# fout.write("\t\t |\tp = Parich_vector(r) = " + str(p) + "\n")

	# fout.write("\t\t |\tfor each c in ALPHABET:\n")
	for c in letters[:K]:
		# fout.write("\t\t |\t\tc=" + str(c) + "\n")
		if p[c] > 0:
			# fout.write("\t\t |\t\tp[" + c + "] > 0\n")
			# fout.write("\t\t |\t\t\tu = w + c = " + w + c + "\n")
			u = w + c
			# fout.write("\t\t |\t\t\tq = p = " + str(p) + "\n")
			q = copy.deepcopy(p)
			# fout.write("\t\t |\t\t\tq[" + c + "] -= 1; q = " + str(q) + "\n")
			q[c] -= 1
			if has_no_forbidden_proper_suffixes(u):
				# fout.write("\t\t |\t\t\tu (" + u + ") has_no_forbidden_proper_suffixes\n")
				# fout.write("\t\t |\t\t\t\tbuild(u=" + u + ", r=" + r + ", q=" + str(q) + ")\n")
				# fout.write("\t\t " + ("-" * 30) + "\n")
				build(u, r, q)
			# fout.write("\t\t " + ("-" * 30) + "\n")


def iterate(Q, R):
	# fout.write("" + ("_" * 30) + "\n")
	# fout.write("ITERATE(Q=" + str(Q) + ", R=" + str(R) + "):\n")
	Q.append((to_sym(0), 0))
	# fout.write("\twhile Q:\n")
	while Q:
		r, t = Q[0]; Q = Q[1:]
		# fout.write("\t\t(" + r + ", " + str(t) + ") pop form Q\n")
		build(r, r, Parich_vector(r))
		if len(r) < R:
			# fout.write("\t\t|r| (" + str(len(r)) + ") < R (" + str(R) + ")\n")
			# fout.write("\t\tfor each c in [0; t]:\n")
			for c in range(t + 1):
				# fout.write("\t\t\tc=" + to_sym(c) + "\n")
				if has_no_forbidden_proper_suffixes("a" + r + to_sym(c)):
					# fout.write("\t\t\t\t rc (" + r + to_sym(c) + ") has_no_forbidden_proper_suffixes\n")
					# fout.write("\t\t\t\tQ.append(" + r + to_sym(c) + ", " + str(t) + ")\n")
					Q.append((r + to_sym(c), t))
			if t + 1 < K:
				# fout.write("\t\tif t+1 ("+ str(t+1) + ") < K:\n")
				# fout.write("\t\t\tQ.append(" + r + to_sym(t+1) + ", " + str(t+1) + ")\n")
				Q.append((r + to_sym(t+1), t+1))


def test_forbidden_suff():
	print(has_no_forbidden_proper_suffixes("ababababab"))
 
	print(has_no_forbidden_proper_suffixes("aaaa"))
	print(has_no_forbidden_proper_suffixes("bbbb"))
	
	assert is_abelian("abbbabbbaab", "abb")

	print(has_no_forbidden_proper_suffixes("aaaaaaabbbabbbaab"))
	print(has_no_forbidden_proper_suffixes("aaabbbabbbaab"))


def test_satisfied_lemma_4_2():
	words = ["aabaabaabaa"]
	roots = ["aab"]
	for i in range(len(words)):
		print(
			words[i],
			roots[i],
			satisfied_lemma_4_2(len(words[i]), len(roots[i]), "Strong")
		)


def main():
	# all possible roots of lexmin words in an auxiliary queue Q
	Q = list()
	R = 1

	tries_len = []
	for R in range(1, 4):
		print("\nIterate, R=" + str(R))
		start_time = time.time()
		iterate(Q, R)
		end_time = time.time()
		tries_len.append(len(trie))
		print("\t|trie| = {}; computated in {} seconds".format(str(tries_len[R-1]), int(end_time - start_time)))

		if R > 1:
			print("\ttrie[{}] / trie[{}] = {}".format(R, R-1, str(float(tries_len[R-1]) / tries_len[R-2])))

		print("Correct - trie")
		print(sorted(list(correct_trie.difference(trie))))
		
		print("\nTrie - correct")
		print(sorted(list(trie.difference(correct_trie))))


if __name__ == '__main__':
	main()
