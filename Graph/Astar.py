import matplotlib.pyplot as plt


class AStarGraph:
    def __init__(self):
        self.barriers = []
        self.barriers.append([(2,4),(2,5),(2,6),(3,6),(4,6),(5,6),(5,5),(5,4),(5,3),(5,2),(4,2),(3,2)])

    def heuristic(self, start, goal):
        "Chebyshev distance"
        dx = abs(start[0] - goal[0])
        dy = abs(start[1] - goal[1])
        return dx + dy - min(dx, dy)

    def getNeighbors(self, pos):
        n = []
        for dx, dy in [(1,0),(-1,0),(0,1),(0,-1),(1,1),(-1,1),(1,-1),(-1,-1)]:
            x = pos[0] + dx
            y = pos[1] + dy
            if x < 0 or x > 7 or y < 0 or y > 7:
                continue
            n.append((x, y))
        return n

    def moveCost(self, a, b):
        for barrier in self.barriers:
            if b in barrier:
                return float('inf')
        return 1


def AStarSearch(start, end, graph):
    G = {} #Actual movement cost to each position from the start position
    F = {} #Estimated movement cost of start to end going via this position

    G[start] = 0
    F[start] = G[start] + graph.heuristic(start, end)

    closedVertices = set()
    openVertices = set([start])
    previous = {}

    while len(openVertices) > 0:
        current = None
        currentFscore = None
        for pos in openVertices:
            if current is None or F[pos] < currentFscore:
                currentFscore = F[pos]
                current = pos

        #Reach the goal
        if current == end:
            path = [current]
            while current in previous:
                current = previous[current]
                path.append(current)
            path.reverse()
            return path, F[end]

        openVertices.remove(current)
        closedVertices.add(current)

        #Update scores for vertices near current
        for neighbor in graph.getNeighbors(current):
            if neighbor in closedVertices:
                continue
            candidateG = G[current] + graph.moveCost(current, neighbor)

            if neighbor not in openVertices:
                openVertices.add(neighbor)
            elif candidateG >= G[neighbor]:
                continue

            previous[neighbor] = current
            G[neighbor] = candidateG
            H = graph.heuristic(neighbor, end)
            F[neighbor] = G[neighbor] + H

    raise RuntimeError("A* failed to find a solution")


if __name__=="__main__":
    graph = AStarGraph()
    result, cost = AStarSearch((0,0), (7,7), graph)

    print ("route", result)
    print ("cost", cost)
    plt.plot([v[0] for v in result], [v[1] for v in result])
    for barrier in graph.barriers:
        plt.plot([v[0] for v in barrier], [v[1] for v in barrier])
    plt.xlim(-1,8)
    plt.ylim(-1,8)
    plt.show()