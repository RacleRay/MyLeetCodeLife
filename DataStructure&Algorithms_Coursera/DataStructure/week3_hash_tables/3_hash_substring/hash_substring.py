# python3
import random


def read_input():
    return (input().rstrip(), input().rstrip())

def print_occurrences(output):
    print(' '.join(map(str, output)))

def get_occurrences_naive(pattern, text):
    return [
        i
        for i in range(len(text) - len(pattern) + 1)
        if text[i:i + len(pattern)] == pattern
    ]

def _polyhash(string, prime, random_x):
    # string hash algorithm
    hash_value = 0
    for s in reversed(string):
        hash_value = (hash_value * random_x + ord(s)) % prime
    return hash_value

def _precompute_hash(text, pattern_len, prime, random_x):
    # 递推求解相邻的近似序列的哈希值
    text_len = len(text)

    hash_list = [-1 for _ in range(text_len - pattern_len + 1)]  # 哈希值储存表
    last_string = text[text_len - pattern_len: ]

    hash_list[-1] = _polyhash(last_string, prime, random_x)

    # Rabin Karp`s algorithm optimize
    x_ = 1  # 见算法递推公式
    for _ in range(pattern_len):  # 防止数值过大
        x_ = (x_ * random_x) % prime

    for i in range(text_len - pattern_len - 1, -1, -1):
        # 防止(−2)%5̸= 3%5的情况，不同编程语言不同
         temp = (random_x * hash_list[i + 1]\
                + ord(text[i])\
                - x_ * ord(text[i + pattern_len])) % prime
         hash_list[i] = (temp + prime) % prime

    return hash_list

def get_occurrences(pattern, text):
    result = []
    pattern_len = len(pattern)
    text_len = len(text)

    prime = 1000000007
    random_x = random.randint(1, prime - 1)

    pattern_hash = _polyhash(pattern, prime, random_x)
    hash_list = _precompute_hash(text, pattern_len, prime, random_x)

    for i in range(text_len - pattern_len + 1):
        if pattern_hash != hash_list[i]:  # 比较目标与query的hash值
            continue
        if text[i: i + pattern_len] == pattern:
            result.append(i)

    return result


if __name__ == '__main__':
    print_occurrences(get_occurrences(*read_input()))

