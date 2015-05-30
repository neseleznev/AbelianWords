#!/usr/bin/env python3
# -*- coding: cp1251 -*-
import Queue, sys, copy
import math

K = 2
beta = 11.0 / 3.0
letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']

correct_trie = {
	"aaaa",

	"aabaabaabaa",
	"aabaababaaa",
	"aabaabbaaaa",
		"aababaaabaa",
		"aababaabaaa",
		"aabababaaaa",
			"aabbaaaabaa",
			"aabbaaabaaa",
			"aabbaabaaaa",

	"abaabaaabab",
	"abaabaabaab",
	"abaababaaab",
		"abaaabaabab",
		"abaaababaab",
		"abaaabbaaab",
			"ababaaaabab",
			"ababaaabaab",
			"ababaabaaab",

	"abbabbabbab",
	"abbabbbabab",
	"abbabbbbaab",
		"abbbababbab",
		"abbbabbabab",
		"abbbabbbaab",
			"abbbbaabbab",
			"abbbbababab",
			"abbbbabbaab",
}
trie = set()

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
	'''Checks whether w is a (weak, semistrong, strong)
	Abelian power with the root r.'''

	if w == r:
		return False

	if not satisfied_lemma_4_2(len(w), len(r), "Strong"):  #<<type??
		return False

	for i in range(0, len(w) // len(r)):
		if not Parich_vector(w[0:len(r)]) == Parich_vector(w[i*len(r) : (i+1)*len(r)]):
			return False

	tail_len = len(w) % len(r)
	tail = w[-tail_len:]
	if tail_len == 0:
		return "Strong"  # Strong (int) Abelian degree

	if Parich_vector(tail) == Parich_vector(w[0:tail_len]):
		return "Strong"

	componentwise_max = Parich_vector("")
	for i in range(0, len(w) // len(r)):
		componentwise_max.plus(
			Parich_vector(w[i*len(r) : (i+1)*len(r)][:tail_len])
		)
	if Parich_vector(tail) <= componentwise_max:
		return "Semi-strong"

	if Parich_vector(tail) <= Parich_vector(w[:len(r)]):
		return "Weak"

	return False


def satisfied_lemma_4_2(w, r, w_type):
	''' Checks whether len(w) satisfies Lemma 4.2
		w = len(w), r = len(r), w_type is type of Abelian period
	'''
	if w_type == "Weak":
		if w == int(math.ceil(r * beta)):
			return True
	elif w_type == "Strong" or w_type == "Semi-strong":
		if int(math.ceil(r * beta)) <= w <= int(r * math.ceil(beta)):
			return True
	return False


def has_no_forbidden_proper_suffixes(w):
	# TODOOO 1 < beta < 2 for weak
	# return True
	if type(beta) == type(1):  # beta is integer
		w = w[::-1]
		for pref_len in range(1, len(w)):
			# print("\t(int) " + w[:pref_len])
			if w[:pref_len] in trie:
				return False
		return True

	# beta is not integer
	for suff_len in range(1, len(w)):
		for root_len in range(1, int((len(w) - suff_len + 1) / math.floor(beta))):
			# print("\t" + w[suff_len:] + " " + w[suff_len : suff_len+root_len])
			if is_abelian(w[suff_len:], w[suff_len : suff_len+root_len]):
				return False
	return True


def build(w, r, p):
	w_type = is_abelian(w, r)
	if w_type:
		if satisfied_lemma_4_2(len(w), len(r), w_type):
			trie.add(w)
			''' TODOOOOOOOO MOTHERFUCKAAAAAA '''
		return

	# if len(w) equals the upper bound from Lemma 4.2
	weak_upper_bound = (
		is_abelian(w, r) == "Weak" and
		len(w) == int(math.ceil( len(r)*beta ))
	)
	strong_upper_bound = (
		(is_abelian(w, r) == "Strong" or is_abelian(w, r) == "Semi-strong") and
		len(w) == len(r) * int(math.ceil( beta ))
	)
	if weak_upper_bound or strong_upper_bound:
		return

	if len(w) % len(r) == 0:
		p = Parich_vector(r)

	for c in letters[:K]:
		if p[c] > 0:
			u = w + c
			q = copy.deepcopy(p)
			q[c] -= 1
			if has_no_forbidden_proper_suffixes(u):
				build(u, r, q)


def iterate(Q, R):
	Q.append((to_sym(0), 0))
	while Q:
		# print("\t" + str(Q))
		r, t = Q[0]; Q = Q[1:]
		print(len(r))
		# print(R, r,t)
		build(r, r, Parich_vector(r))
		if len(r) < R:
			for c in range(t + 1):
				# print(to_sym(c))
				if has_no_forbidden_proper_suffixes(r + to_sym(c)): #has no forbidden sufixes
					Q.append((r + to_sym(c), t))
			if t + 1 < K:
				# print(t)
				Q.append((r + to_sym(t+1), t+1))


def test_forbidden_suff():
	print(has_no_forbidden_proper_suffixes("ababababab"))
 
	print(has_no_forbidden_proper_suffixes("aaaa"))
	print(has_no_forbidden_proper_suffixes("bbbb"))
	
	assert is_abelian("abbbabbbaab", "abb") == "Strong"

	print(has_no_forbidden_proper_suffixes("aaaaaaabbbabbbaab"))
	print(has_no_forbidden_proper_suffixes("aaabbbabbbaab"))


def test_satisfied_lemma_4_2():
	satisfied_lemma_4_2()

def main():
	# all possible roots of lexmin words in an auxiliary queue Q
	Q = list()
	R = 1
	for R in range(1, 12):
		iterate(Q, R)
	print(trie)

	#test_forbidden_suff()

if __name__ == '__main__':
	main()
