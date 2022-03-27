from typing import Generic, TypeVar, Dict, List, Optional
from abc import ABC, abstractmethod

V = TypeVar('V')
D = TypeVar('D')


class Constraint(Generic[V, D], ABC):
    def __init__(self, variables: List[V]) -> None:
        self.variables = variables

    @abstractmethod
    def satisfied(self, assignment: Dict[V, D]) -> bool:
        ...


class CSP(Generic[V, D]):
    def __init__(self, variables: List[V], domains: Dict[V, List[D]]) -> None:
        self.variables: List[V] = variables
        self.domains: Dict[V, List[D]] = domains
        self.constraints: Dict[V, List[Constraint[V, D]]] = {}
        for variable in self.variables:
            self.constraints[variable] = []
            if variable not in self.domains:
                raise LookupError("domain中找不到变量名称")

    def add_constraint(self, constraints: Constraint[V, D]) -> None:
        for variable in constraints.variables:
            if variable not in self.variables:
                raise LookupError("找不到变量名称")
            else:
                self.constraints[variable].append(constraints)

    def consistent(self, variable: V, assignment: Dict[V, D]) -> bool:
        "条件检测"
        for constraint in self.constraints[variable]:
            if not constraint.satisfied(assignment):
                return False
        return True

    def backtracking_search(self,
                            assignment: Dict[V, D] = {}) -> Optional[Dict[V, D]]:
        if len(assignment) == len(self.variables):
            return assignment

        unassigned: List[V] = [
            v for v in self.variables if v not in assignment
        ]

        first: V = unassigned[0]
        for val in self.domains[first]:
            local_assignment = assignment.copy()
            local_assignment[first] = val
            if self.consistent(first, local_assignment):
                result: Optional[Dict[V, D]] = self.backtracking_search(
                    local_assignment)
                if result is not None:
                    return result
        return None


################################################################
# Example : Map Coloring


class MapColoringConstraint(Constraint[str, str]):
    def __init__(self, place1: str, place2: str) -> None:
        super().__init__([place1, place2])
        self.place1 = place1
        self.place2 = place2

    def satisfied(self, assignment: Dict[str, str]) -> bool:
        if self.place1 not in assignment or self.place2 not in assignment:
            return True
        return assignment[self.place1] != assignment[self.place2]


if __name__ == "__main__":

    variables: List[str] = [
        "Western Australia", "Northern Territory", "South Australia",
        "Queensland", "New South Wales", "Victoria", "Tasmania"
    ]
    domains: Dict[str, List[str]] = {}
    for variable in variables:
        domains[variable] = ["red", "green", "blue"]

    csp: CSP[str, str] = CSP(variables, domains)
    csp.add_constraint(
        MapColoringConstraint("Western Australia", "Northern Territory"))
    csp.add_constraint(
        MapColoringConstraint("Western Australia", "South Australia"))
    csp.add_constraint(
        MapColoringConstraint("South Australia", "Northern Territory"))
    csp.add_constraint(
        MapColoringConstraint("Queensland", "Northern Territory"))
    csp.add_constraint(MapColoringConstraint("Queensland", "South Australia"))
    csp.add_constraint(MapColoringConstraint("Queensland", "New South Wales"))
    csp.add_constraint(
        MapColoringConstraint("New South Wales", "South Australia"))
    csp.add_constraint(MapColoringConstraint("Victoria", "South Australia"))
    csp.add_constraint(MapColoringConstraint("Victoria", "New South Wales"))
    csp.add_constraint(MapColoringConstraint("Victoria", "Tasmania"))

    # 求解
    solution: Optional[Dict[str, str]] = csp.backtracking_search()
    if solution is None:
        print("No solution found!")
    else:
        print(solution)