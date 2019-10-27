# python3
import sys


def sortChar(string):
  """O(#s + #char). Textcontains symbols A, C, G, T only"""
  order = [0 for _ in range(len(string))]
  count = [0 for _ in range(5)]
  index_map = {'$': 0, 'A': 1, 'C': 2, 'G': 3, 'T': 4}

  for i in range(0, len(string)):
    count[index_map[string[i]]] += 1
  for j in range(1, 5):
    count[j] += count[j - 1]  # cum sum
  for i in range(len(string) - 1, -1, -1):
    char = string[i]
    count[index_map[char]] -= 1
    order[count[index_map[char]]] = i  # sort index of every char position

  return order

def computeCharClasses(string, order):
  """O(#s)"""
  clas = [0 for _ in range(len(string))]

  for i in range(1, len(string)):
    # new char, new class
    if string[order[i]] != string[order[i - 1]]:
      clas[order[i]] = clas[order[i - 1]] + 1
    else:
      clas[order[i]] = clas[order[i - 1]]

  return clas

def sortDoubled(string, L, order, cls):
  """O(#s)"""
  count = [0 for _ in range(len(string))]
  newOrder = [0 for _ in range(len(string))]

  # count sort: stable sort
  for i in range(0, len(string)):
    count[cls[i]] += 1
  for j in range(1, len(string)):
    count[j] += count[j - 1]
  for i in range(len(string) - 1, -1, -1):
    # the part to be sorted
    start = (order[i] - L + len(string)) % len(string)  # cycle index
    clas_ = cls[start]
    count[clas_] -= 1
    newOrder[count[clas_]] = start

  return newOrder

def updateClasses(order, cls, L):
  """O(#s)"""
  n = len(order)
  newClass = [0 for _ in range(n)]
  for i in range(1, n):
    cur = order[i]
    prev = order[i - 1]
    mid = (cur + L) % n
    midprev = (prev + L) % n

    # 分两个L长度的部分比较
    if cls[cur] != cls[prev] or cls[mid] != cls[midprev]:
      newClass[cur] = newClass[prev] + 1
    else:
      newClass[cur] = newClass[prev]

  return newClass

def build_suffix_array(text):
  """
  Build suffix array of the string text and
  return a list result of the same length as the text
  such that the value result[i] is the index (0-based)
  in text where the i-th lexicographically smallest
  suffix of text starts.
  """
  order = sortChar(text)
  clas = computeCharClasses(text, order)
  L = 1

  while L < len(text):
    order = sortDoubled(text, L, order, clas)
    clas = updateClasses(order, clas, L)
    L *= 2

  return order


def pattern_match_suffix_array(text, pattern, suffixArray):
    """find the first one algo."""
    minIndex = 0
    maxIndex = len(text)
    while minIndex < maxIndex:
        midIndex = (minIndex + maxIndex) // 2
        if pattern > suffixArray[midIndex]:
            minIndex += 1
        else:
            maxIndex = midIndex

    start = minIndex
    maxIndex = len(text)
    while minIndex < maxIndex:
        midIndex = (minIndex + maxIndex) // 2
        if pattern < suffixArray[midIndex]:
            maxIndex = midIndex
        else:
            minIndex += 1

    end = maxIndex
    if start > end:
        return (None, None)
    else:
        return (start, end)


def find_occurrences(text, patterns):
    occs = set()
    suffixorder = build_suffix_array(text)
    # suffixArray = [text[i:] for i in suffixorder]

    for pattern in patterns:
        for index in suffixorder:
            if len(text) - index >= len(pattern) and pattern == text[index: ][: len(pattern)]:
                occs.add(index)

    # find find the first one algo
    # for pattern in patterns:
    #     start, end = pattern_match_suffix_array(txt, pattern, suffixArray)
    #     occs.add(start)

    return occs


if __name__ == '__main__':
    text = sys.stdin.readline().strip()
    pattern_count = int(sys.stdin.readline().strip())
    patterns = sys.stdin.readline().strip().split()
    occs = find_occurrences(text, patterns)
    print(" ".join(map(str, occs)))

# AAA
# 1
# A

# ATA
# 3
# C G C

# ATATATA
# 3
# ATA C TATAT