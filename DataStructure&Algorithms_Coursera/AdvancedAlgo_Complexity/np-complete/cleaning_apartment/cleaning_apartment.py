# python3
import itertools


n, m = map(int, input().split())
edges = [ list(map(int, input().split())) for i in range(m) ]


def get_adjacent(v, edges):
    adjacent=[]
    for e in edges:
        if v in e:
            adjacent += [i for i in e if i != v]
    return set(adjacent)


def printEquisatisfiableSatFormula():
    """对比 sudokusolver.py
       n: the number of vertices
       m: the number of edges
      The first line contains two integers n and m — the number of rooms and the number of corridors
    connecting the rooms respectively. Each of the next m lines contains two integers u and v
    describing the corridor going from room u to room v. The corridors are two-way, that is,
    you can go both from u to v and from v to u. No two corridors have a common part, that is,
    every corridor only allows you to go from one room to one other room.
    """
    clauses = []
    var_map = {}

    # 位置是确定的，点可以移动
    # i行j列，var设置为 i*100 + j。1≤ n ≤30，所以 * 100 是安全的
    counter = 1
    for i in range(1, n + 1):
        clause = []
        for j in range(1, n + 1):
            clause.append(i*100 + j)
            var_map[i*100 + j] = counter
            counter += 1
        clauses.append(clause)

    for o in range(1, n + 1):
        cl = [j * 100 + o for j in range(1, n+1)]
        # 需要每一个点都在该路径上出现
        for pair in itertools.combinations(cl, 2):
            if [-pair[1],-pair[0]] not in clauses and [-pair[0],-pair[1]] not in clauses:
                clauses.append([-d for d in pair])

    for o in range(1, n + 1):
        # 两个不同的点在该路径上占据不同位置
        for e in range(1, n):
            cl = [-(o * 100 + e)]
            for j in get_adjacent(o, edges):
                cl.append(j * 100 + e + 1)
            clauses.append(cl)

    for e in range(0, len(clauses)):
        for d in range(0, len(clauses[e])):
            if clauses[e][d] >= 0:
                clauses[e][d] = var_map[clauses[e][d]]
            else:
                clauses[e][d] = -var_map[-clauses[e][d]]

    print(len(clauses),n * n)
    for l in clauses:
        print(" ".join(map(str, l)),0)


# 5 4
# 1 2
# 2 3
# 3 5
# 4 5

printEquisatisfiableSatFormula()