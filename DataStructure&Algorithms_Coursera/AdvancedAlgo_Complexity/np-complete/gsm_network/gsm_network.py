# python3
import itertools

n, m = map(int, input().split())
edges = [ list(map(int, input().split())) for i in range(m) ]


# This solution prints a simple satisfiable formula
# and passes about half of the tests.
# Change this function to solve the problem.
def printEquisatisfiableSatFormula():
    """n: the number of vertices
       m: the number of edges
    The vertices are numbered from 1 through n. Each of the next m lines contains
    two integers u and v — the numbers of vertices connected by an edge.
    It is guaranteed that a vertex cannot beconnected to itself by an edge
    """
    list_formulas = [''] # first index will contain length
    var_map = {} # dict that will map all vars to the natural numbers.
    counter = 1
    # 每个节点只能选择一个颜色，一个var表示节点和颜色的一个组合，这个组合成为了新的节点，counter为编号
    for vertex in range(1, n + 1):
        vars = []
        for i in range(1, 4): # 三种颜色
            vertex_var = str(vertex) + str(i)
            var_map[vertex_var] = counter
            counter += 1
            vars.append(str(var_map[vertex_var]))

        # 类似 sudokusolver 方法，一个点只有一种颜色，转化为并列的新节点的clause
        formulas = []
        formulas.append(' '.join(vars + ['0']))
        for u, v in itertools.combinations(vars, 2):
            formulas.append('-{} -{} 0'.format(u, v))
        list_formulas.extend(formulas)

    # add CNF that no two vertices have the same color
    for source, sink in edges:
        for i in range(1, 4):
            source_var = str(source) + str(i)
            sink_var = str(sink) + str(i)
            list_formulas.append('-{} -{} 0'.format(var_map[source_var], var_map[sink_var]))
    # all clauses are in list, and all vars are in the set
    list_formulas[0] = '{} {}'.format(len(list_formulas) - 1, 3 * n)

    print('\n'.join(list_formulas))


printEquisatisfiableSatFormula()

# 3 3
# 1 2
# 2 3
# 1 3