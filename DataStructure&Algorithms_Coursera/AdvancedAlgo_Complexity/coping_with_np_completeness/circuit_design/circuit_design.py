# python3
import threading
import sys

# This code is used to avoid stack overflow issues
sys.setrecursionlimit(10**6) # max depth of recursion
threading.stack_size(2**26)  # new thread will get stack of such size

n, m = map(int, input().split())
clauses = [ list(map(int, input().split())) for i in range(m) ]

# This solution tries all possible 2^n variable assignments.
# It is too slow to pass the problem.
# Implement a more efficient algorithm here.
def isSatisfiable_naive():
    for mask in range(1<<n):
        result = [ (mask >> i) & 1 for i in range(n) ]
        formulaIsSatisfied = True
        for clause in clauses:
            clauseIsSatisfied = False
            if result[abs(clause[0]) - 1] == (clause[0] < 0):
                clauseIsSatisfied = True
            if result[abs(clause[1]) - 1] == (clause[1] < 0):
                clauseIsSatisfied = True
            if not clauseIsSatisfied:
                formulaIsSatisfied = False
                break
        if formulaIsSatisfied:
            return result
    return None


class Vertex:
    def __init__(self, u):
        self.index = u
        self.value = -1 # the value the vertex becomes in the CNF when satisfied
        self.out_neighbors = [] # vertices that can be traversed in the forward direction (u -> v)
        self.in_neighbors = [] # vertices that can be traversed in the backward direction (t -> u)
        self.scc = set() # strongly connected components of this vertex
        self.root = False # will determine if this is the root of the SCC

        self.lowlink = -1 # smallest discovered vertex reachable from this one
        self.discovered = -1 # when it was discovered
        self.on_stack = False


def implication_graph(clauses):
    # for each variablex, introduce twovertices labeled by x and x_;
    # for each 2-clause(ℓ1∨ℓ2), introducetwo directed edges ℓ1_→ℓ2 and ℓ2_→ℓ1
    # for each 1-clause(ℓ), introduce an edge ℓ_→ℓ
    # if there is an edge ℓ1→ℓ2, then there is an edge ℓ2_→ℓ1_
    graph = {} # u -> v stored as [u, v]

    for i in range(1, n + 1):
        graph[i] = Vertex(i)
        graph[-i] = Vertex(-i)

    for clause in clauses:
        u = clause[0]
        if len(clause) == 1:
            graph[-u].out_neighbors.append(u)
            graph[u].in_neighbors.append(-u)

        elif len(clause) == 2:
            v = clause[1]
            graph[-u].out_neighbors.append(v)
            graph[v].in_neighbors.append(-u)
            graph[-v].out_neighbors.append(u)
            graph[u].in_neighbors.append(-v)

    return graph


def tarjans(graph):
    """ uses Tarjan's Algorithm to generate the SCCs.
    returns a list of roots in reverse topological order. """
    index = 0
    stack = []
    roots = []
    for vertex in graph.keys():
        if graph[vertex].discovered == -1:
            strong_connect(graph[vertex], stack, index, graph, roots)
            # print(stack, roots)
    return roots


def strong_connect(vertex, stack, index, graph, roots):
    """ Helper for Tarjan's. Generates the SCCs. vertex input is the Vertex object. """
    vertex.discovered = index
    vertex.lowlink = index
    index += 1
    stack.append(vertex)
    vertex.on_stack = True

    for out_vertex_index in vertex.out_neighbors:
        if graph[out_vertex_index].discovered == -1:
            # not visited; recurse
            strong_connect(graph[out_vertex_index], stack, index, graph, roots)
            vertex.lowlink = min(vertex.lowlink, graph[out_vertex_index].lowlink)
        elif graph[out_vertex_index].on_stack:
            # the vertex is on the stack; back edge case
            # the out_vertex is the root
            vertex.lowlink = min(vertex.lowlink, graph[out_vertex_index].discovered)

    # generate the SCC if conditions are correct
    if vertex.discovered == vertex.lowlink:
        while len(stack) != 0:
            v = stack.pop(-1)
            vertex.scc.add(v.index)
            v.on_stack = False
            # pop the stack only up and including the current root
            if v == vertex:
                break
        # while vertex != v
        roots.append(vertex.index)


def isSatisfiable():
    """Very Large-Scale Integration is a process of creating an integrated circuit by
    combiningthousands of transistors on a single chip.
    The wires will be all on the same layer, but they cannot intersect with each other.
    Also, each wire can only be bent once, in one of two directions — to the left or
    to the right.  Youneed to determine a position for each wire in such a way that
    no wires intersect.

    This problem can be reduced to 2-SAT problem. — a special case of the SAT problem
    in which eachclause contains exactly2variables.
    A binary variable which takes value 1 if the wire is bent to the right and 0 if the
    wire is bent to the left.
    """
    graph = implication_graph(clauses)

    roots = tarjans(graph)

    # x only has one value in scc
    for vertex in roots:
        if -vertex in graph[vertex].scc:
            return None
        for literal in graph[vertex].scc:
            if -literal in graph[vertex].scc:
                return None

    result = [None] * n
    for scc_root in roots:

        for literal in graph[scc_root].scc:
            if graph[literal].value == -1:
                graph[literal].value = 1
                result[abs(literal) - 1] = literal
                graph[-literal].value = 0

    return result


# 1 2
# 1 1
# -1 -1

# 3 3
# 1 -3
# -1 2
# -2 -3

def main():
    result = isSatisfiable()
    if result is None:
        print("UNSATISFIABLE")
    else:
        print("SATISFIABLE");
        print(" ".join([str(i) for i in result]))


threading.Thread(target=main).start()