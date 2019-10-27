# python3
import sys


def PreprocessBWT(bwt):
  """
  Preprocess the Burrows-Wheeler Transform bwt of some text
  and compute as a result:
    * starts - for each character C in bwt, starts[C] is the first position
        of this character in the sorted array of
        all characters of the text.
    * occ_count_before - for each character C in bwt and each position P in bwt,
        occ_count_before[C][P] is the number of occurrences of character C in bwt
        from position 0 to position P inclusive.
  """
  starts = {}
  occ_count_before = {}
  chars = {'$', 'A', 'C', 'G', 'T'}

  for char in chars:
    occ_count_before[char] = [0 for _ in range(len(bwt) + 1)]

  # 不同char在每个位置的累计count
  for i in range(len(bwt)):
    char = bwt[i]
    for c, count in occ_count_before.items():
        count[i + 1] = count[i]
    occ_count_before[char][i + 1] = occ_count_before[char][i] + 1

  # 相同char的开始index
  index = 0
  for char in sorted(chars):
    starts[char] = index
    index += occ_count_before[char][len(bwt)]

  return starts, occ_count_before


def CountOccurrences(pattern, bwt, starts, occ_counts_before):
  """
  Compute the number of occurrences of string pattern in the text
  given only Burrows-Wheeler Transform bwt of the text and additional
  information we get from the preprocessing stage - starts and occ_counts_before.
  """
  top = 0
  bottom = len(bwt) - 1
  cur_index = len(pattern) - 1

  while top <= bottom:
    if cur_index >= 0:
      symbol = pattern[cur_index]  # last symbol in pattern
      cur_index -= 1  # remove last symbol

      top = starts[symbol] + occ_counts_before[symbol][top]
      bottom = starts[symbol] + occ_counts_before[symbol][bottom + 1] - 1

    else:
      return bottom - top + 1

  return 0



if __name__ == '__main__':
  bwt = sys.stdin.readline().strip()
  pattern_count = int(sys.stdin.readline().strip())
  patterns = sys.stdin.readline().strip().split()
  # Preprocess the BWT once to get starts and occ_count_before.
  # For each pattern, we will then use these precomputed values and
  # spend only O(|pattern|) to find all occurrences of the pattern
  # in the text instead of O(|pattern| + |text|).
  starts, occ_counts_before = PreprocessBWT(bwt)
  occurrence_counts = []
  for pattern in patterns:
    occurrence_counts.append(CountOccurrences(pattern, bwt, starts, occ_counts_before))
  print(' '.join(map(str, occurrence_counts)))
# AGGGAA$
# 1
# GA

# AT$TCTATG
# 2
# TCT
# TATG