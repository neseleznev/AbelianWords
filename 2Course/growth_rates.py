#!/usr/bin/env python3
# -*- coding: cp1251 -*-
import queue, sys, copy
import math


class MyException(Exception):
	def __init__(self, value):
		self.value = value
	def __str__(self):
		return repr(self.value)


class DiGraph:

	def __init__(self, n):
		self.n = n
		self.adj = [ [] for i in range(self.n) ]

	def reverse(self):
		self.reversed = DiGraph(self.n)
		for i in range(self.n):
			for j in self[i]:
				self.reversed[j].append(i)

	def __getitem__(self, ind):
		return self.adj[ind]


def find_all_scc(A):
	components = []

	def dfs1(v):
		used[v] = True
		for u in A[v]:
			if not used[u]:
				dfs1(u)
		order.append(v)

	def dfs2(v):
		used[v] = True
		component.append(v)
		for u in A.reversed[v]:
			if not used[u]:
				dfs2(u)

	A.reverse()
	order = []
	component = []

	used = [False for i in range(A.n)]
	for i in range(A.n):
		if not used[i]:
			dfs1(i)

	used = [False for i in range(A.n)]
	for i in range(A.n):
		v = order[A.n - 1 - i]
		if not used[v]:
			dfs2(v)
			components.append(component)
			component = []

	return components

def there_are_cycles(A, components):
	for scc in components:
		if is_cycle(A, scc):
			return True
	return False

def is_cycle(A, scc):
	
	def curr_path(v):
		path = []
		vert = v
		while vert != -1:
			path.append(vert)
			vert = p[vert]
		return path[::-1]

	q = [ scc[0] ]
	used = [False for i in range(A.n)]
	used[scc[0]] = True
	p = [-1 for i in range(A.n)]
	while q:
		v = q[0]; q = q[1:]
		for u in A[v]:
			if used[u]:
				if set(curr_path(v)) == set(scc):
					return True
			else:
				used[u] = True
				q.append(u)
				p[u] = v
	return False

def all_scc_are_cycles_or_singletons(A, components):
	for scc in components:
		if len(scc) == 1 or is_cycle(A, scc):
			continue
		else:
			return False
	return True


def algorithm_1(A, delta):
	'''
	Algorithm 1.
		Input: consistent dfa A, number delta: 0 < delta < 1.
		Output: number alpha such that |alpha − α(A)| < delta.
	'''
	scc = find_all_scc(A)
	print(scc)
	if all_scc_are_cycles_or_singletons(A, scc):
		if there_are_cycles(A, scc):
			return 1
		else:
			return 0

	old = [-1 for _ in range(A.n)]
	new = [-1 for _ in range(A.n)]
	alphs = [-1e-15 for _ in range(A.n)]


	for i in range(len(scc)):
		if len(scc[i]) > 1:
			for u in scc[i]:
				old[u] = 1
				new[u] = 0
			while True:
				for u in scc[i]:
					for v in A[u]:
						new[v] += old[u]
					new[u] += old[u]

				minrate = min(new[u] / float(old[u]) for u in scc[i])
				maxrate = max(new[u] / float(old[u]) for u in scc[i])

				if maxrate - minrate < 2 * delta:
					alphs[i] = (maxrate+minrate) / 2.0
					break

				for u in scc[i]:
					old[u] = new[u]
					new[u] = 0
	return max(alphs) - 1


def algorithm_1Q(A, delta, n):
	'''
	Algorithm 1Q.
		Input: consistent dfa A, number delta: 0 < delta < 1, number n.
		Output: number alpha for which the procedure ORACLE suggests |alpha − α(A)| < delta,
		or the number delta2 which estimates the approximation error after n iterations.
		Initialization: Put old[s] = 1 for the initial vertex s and set all other old and
		new counters to 0. Put comp[0] = 1.
	'''
	for t in range(A.n):
		old[t] = 0
		new[t] = 0
	old[s] = 1
	comp[0] = 1

	for i in range(n):
		for u in range(A.n):
			for v in A[u]:
				new[v] += old[u]
			new[u] += old[u]
		for u in range(A.n):
			comp[i] += new[u]
			old[u] = new[u]; new[u] = 0
		rate[i] = float(comp[i]) / comp[i - 1]
		if ORACLE(rate, delta) == alpha:
			return alpha
			break
	return abs(rate[n] - rate[n - 1])



def main():
	A = DiGraph(4)
	A[0].append(3)
	A[1].append(0)
	A[2].append(3)

	print(algorithm1(A, 0.5))


if __name__ == '__main__':
	main()
