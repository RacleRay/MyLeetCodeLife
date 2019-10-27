# python3
import sys


def solve(p, q):
	# naive
    for i in range(min(len(p), len(q))):
        for j in range(len(p) - i):
            s = p[j: (j + i + 1)]
            if not s in q:
                return s

    return



p = sys.stdin.readline ().strip ()
q = sys.stdin.readline ().strip ()

ans = solve (p, q)

sys.stdout.write (ans + '\n')
