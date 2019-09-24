# python3

import sys
import random
from collections import defaultdict

class Solver:
	def __init__(self, s):
		self.s = s
		self.complete = defaultdict()

	def ask(self, a, b, l):
		# 双重hash，使得collision的概率减小为（n/prime1）*(n/prime2),为string总长度
		prime1 = 10 ** 9 + 7
		prime2 = 10 ** 9 + 9

		random_x = random.randint(1, 10 ** 9)

		hash_list_1 = self._precompute_hash(prime1, random_x)
		hash_list_2 = self._precompute_hash(prime2, random_x)

		hash_a_1 = self._compute_hash(hash_list_1, prime1, random_x, a, l)
		hash_b_1 = self._compute_hash(hash_list_1, prime1, random_x, b, l)

		hash_a_2 = self._compute_hash(hash_list_2, prime2, random_x, a, l)
		hash_b_2 = self._compute_hash(hash_list_2, prime2, random_x, b, l)

		return hash_a_1 == hash_b_1 and hash_a_2 == hash_b_2

	@staticmethod
	def _polyhash(string, prime, random_x):
		# string hash algorithm
		hash_value = 0
		for s in string:
			hash_value = (hash_value * random_x + ord(s)) % prime
		return hash_value

	def _precompute_hash(self, prime, random_x):
		# 递推求解递增序列的哈希值
		text_len = len(self.s)

		hash_list = [0 for _ in range(text_len + 1)]  # 哈希值储存表
		hash_list[1] = self._polyhash(self.s[0], prime, random_x)
		for i in range(2, text_len + 1):
			hash_list[i] = (random_x * hash_list[i - 1] + ord(self.s[i - 1])) % prime

		return hash_list

	def _compute_hash(self, hash_list, prime, random_x, begin, length):
		value_idx_1 = begin + length
		value_idx_2 = begin

		hash_value = self.complete.get((self.s[value_idx_2: value_idx_1], prime))
		if hash_value == None:
			# x_ = 1
			# for _ in range(length):  # 防止数值过大
			# 	 = (x_ * random_x) % prime
			x_ = pow(random_x, length, prime)
			# 递推公式
			hash_value = (hash_list[value_idx_1] - x_ * hash_list[value_idx_2]) % prime
			# 缓存
			self.complete[(self.s[value_idx_2: value_idx_1], prime)] = hash_value

		return hash_value


s = sys.stdin.readline()
q = int(sys.stdin.readline())
solver = Solver(s)
for i in range(q):
	a, b, l = map(int, sys.stdin.readline().split())
	print("Yes" if solver.ask(a, b, l) else "No")
