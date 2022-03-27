# from __future__ import annotations
from typing import TypeVar, Iterable, Sequence, Generic, List, Callable, Set, Deque, Any, Optional
from typing_extensions import Protocol
from heapq import heappush, heappop
from math import sqrt
from utils.maze import MazeLocation, Maze

T = TypeVar('T')
C = TypeVar("C", bound="Comparable")


# ============== binary ==============
class Comparable(Protocol):
    def __eq__(self, other: Any) -> bool:
        ...

    def __lt__(self: C, other: C) -> bool:
        ...

    def __gt__(self: C, other: C) -> bool:
        return (not self < other) and self != other

    def __le__(self: C, other: C) -> bool:
        return self < other or self == other

    def __ge__(self: C, other: C) -> bool:
        return not self < other


def linear_contains(iterable: Iterable[T], key: T) -> bool:
    for item in iterable:
        if item == key:
            return True
    return False


def binary_contains(sequence: Sequence[C], key: C) -> bool:
    low: int = 0
    high: int = len(sequence) - 1
    while low <= high:  # while there is still a search space
        mid: int = (low + high) // 2
        if sequence[mid] < key:
            low = mid + 1
        elif sequence[mid] > key:
            high = mid - 1
        else:
            return True
    return False


# ============== dfs ==============
class Stack(Generic[T]):
    def __init__(self) -> None:
        self._container: List[T] = []

    @property
    def empty(self) -> bool:
        return not self._container  # not is true for empty container

    def push(self, item: T) -> None:
        self._container.append(item)

    def pop(self) -> T:
        return self._container.pop()  # LIFO

    def __repr__(self) -> str:
        return repr(self._container)


class Node(Generic[T]):
    def __init__(self,
                 state: T,
                 parent,
                 cost: float = 0.0,
                 heuristic: float = 0.0) -> None:
        self.state: T = state
        self.parent = parent
        self.cost: float = cost
        self.heuristic: float = heuristic

    def __lt__(self, other) -> bool:
        return (self.cost + self.heuristic) < (other.cost + other.heuristic)


def dfs(initial, goal_func, find_next):
    frontier = Stack()
    frontier.push(Node(initial, None))
    explored = {initial}
    while not frontier.empty:
        current = frontier.pop()
        state = current.state
        if goal_func(state):
            return current
        for child in find_next(state):
            if child in explored:
                continue
            explored.add(child)
            frontier.push(Node(child, current))
    return None


# ============== bfs ==============
class Queue(Generic[T]):
    def __init__(self) -> None:
        self._container: Deque[T] = Deque()

    @property
    def empty(self) -> bool:
        return not self._container  # not is true for empty container

    def push(self, item: T) -> None:
        self._container.append(item)

    def pop(self) -> T:
        return self._container.popleft()  # FIFO

    def __repr__(self) -> str:
        return repr(self._container)


def bfs(initial: T, goal_test: Callable[[T], bool],
        successors: Callable[[T], List[T]]) -> Optional[Node[T]]:
    # frontier is where we've yet to go
    frontier: Queue[Node[T]] = Queue()
    frontier.push(Node(initial, None))
    # explored is where we've been
    explored: Set[T] = {initial}

    # keep going while there is more to explore
    while not frontier.empty:
        current_node: Node[T] = frontier.pop()
        current_state: T = current_node.state
        # if we found the goal, we're done
        if goal_test(current_state):
            return current_node
        # check where we can go next and haven't explored
        for child in successors(current_state):
            if child in explored:  # skip children we already explored
                continue
            explored.add(child)
            frontier.push(Node(child, current_node))
    return None  # went through everything and never found goal


# ============== A* ==============


class PriorityQueue(Generic[T]):
    def __init__(self) -> None:
        self._container: List[T] = []

    @property
    def empty(self) -> bool:
        return not self._container  # not is true for empty container

    def push(self, item: T) -> None:
        heappush(self._container, item)  # in by priority

    def pop(self) -> T:
        return heappop(self._container)  # out by priority

    def __repr__(self) -> str:
        return repr(self._container)


def astar(initial, goal_func, find_next, cal_heuristic):
    frontier = PriorityQueue()
    frontier.push(Node(initial, None, 0.0, cal_heuristic(initial)))
    explored = {initial: 0.0}

    while not frontier.empty:
        current = frontier.pop()
        state = current.state
        if goal_func(state):
            return current
        for child in find_next(state):
            cost = current.cost + 1
            if child not in explored or explored[child] > cost:
                explored[child] = cost
                frontier.push(Node(child, current, cost, cal_heuristic(child)))
    return None


def euclidean_distance(goal: MazeLocation) -> Callable[[MazeLocation], float]:
    def distance(ml: MazeLocation) -> float:
        xdist: int = ml.column - goal.column
        ydist: int = ml.row - goal.row
        return sqrt((xdist * xdist) + (ydist * ydist))

    return distance


def manhattan_distance(goal: MazeLocation) -> Callable[[MazeLocation], float]:
    def distance(ml: MazeLocation) -> float:
        xdist: int = abs(ml.column - goal.column)
        ydist: int = abs(ml.row - goal.row)
        return (xdist + ydist)

    return distance


def node_to_path(node: Node[T]) -> List[T]:
    path: List[T] = [node.state]
    # work backwards from end to front
    while node.parent is not None:
        node = node.parent
        path.append(node.state)
    path.reverse()
    return path


if __name__ == "__main__":
    # ============== binary ==============
    print(linear_contains([1, 5, 15, 15, 15, 15, 20], 5))  # True

    l_1 = sorted(["a", "d", "e", "f", "z"])
    print(binary_contains(l_1, "f"))  # True
    l_2 = sorted(["john", "mark", "ronald", "sarah"])
    print(binary_contains(l_2, "sheila"))  # False

    # Test DFS
    m: Maze = Maze(sparseness=0.2)
    print(m)
    solution1: Optional[Node[MazeLocation]] = dfs(m.start, m.goal_test,
                                                  m.successors)
    if solution1 is None:
        print("No solution found using depth-first search!")
    else:
        path1: List[MazeLocation] = node_to_path(solution1)
        m.mark(path1)
        print(m)
        m.clear(path1)

    # Test BFS
    solution2: Optional[Node[MazeLocation]] = bfs(m.start, m.goal_test,
                                                  m.successors)
    if solution2 is None:
        print("No solution found using breadth-first search!")
    else:
        path2: List[MazeLocation] = node_to_path(solution2)
        m.mark(path2)
        print(m)
        m.clear(path2)

    # Test A*
    distance: Callable[[MazeLocation], float] = manhattan_distance(m.goal)
    solution3: Optional[Node[MazeLocation]] = astar(m.start, m.goal_test,
                                                    m.successors, distance)
    if solution3 is None:
        print("No solution found using A*!")
    else:
        path3: List[MazeLocation] = node_to_path(solution3)
        m.mark(path3)
        print(m)