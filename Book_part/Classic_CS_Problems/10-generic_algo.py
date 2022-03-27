from typing import TypeVar, Generic, List, Tuple, Callable, Type
from enum import Enum
from random import choices, random, randrange
from heapq import nlargest
from statistics import mean
from abc import ABC, abstractmethod
from copy import deepcopy


T = TypeVar('T', bound='Chromosome') # for returning self

# Base class for all chromosomes; all methods must be o overridden
class Chromosome(ABC):
    @abstractmethod
    def fitness(self) -> float:
        ...

    @classmethod
    @abstractmethod
    def random_instance(cls: Type[T]) -> T:
        ...

    @abstractmethod
    def crossover(self: T, other: T) -> Tuple[T, T]:
        ...

    @abstractmethod
    def mutate(self) -> None:
        ...


C = TypeVar('C', bound=Chromosome) # type of the chromosomes


class GeneticAlgorithm(Generic[C]):
    SelectionType = Enum("SelectionType", "ROULETTE TOURNAMENT")

    def __init__(self, initial_population: List[C], threshold: float, max_generations: int = 100, mutation_chance: float = 0.01, crossover_chance: float = 0.7, selection_type: SelectionType = SelectionType.TOURNAMENT) -> None:
        self._population: List[C] = initial_population
        self._threshold: float = threshold
        self._max_generations: int = max_generations
        self._mutation_chance: float = mutation_chance
        self._crossover_chance: float = crossover_chance
        self._selection_type: GeneticAlgorithm.SelectionType = selection_type
        self._fitness_key: Callable = type(self._population[0]).fitness

    # Use the probability distribution wheel to pick 2 parents
    # Note: will not work with negative fitness results
    def _pick_roulette(self, wheel: List[float]) -> Tuple[C, C]:
        return tuple(choices(self._population, weights=wheel, k=2))

    # Choose num_participants at random and take the best 2
    def _pick_tournament(self, num_participants: int) -> Tuple[C, C]:
        participants: List[C] = choices(self._population, k=num_participants)
        return tuple(nlargest(2, participants, key=self._fitness_key))

    # Replace the population with a new generation of individuals
    def _reproduce_and_replace(self) -> None:
        new_population: List[C] = []
        # keep going until we've filled the new generation
        while len(new_population) < len(self._population):
            # pick the 2 parents
            if self._selection_type == GeneticAlgorithm.SelectionType.ROULETTE:
                parents: Tuple[C, C] = self._pick_roulette([x.fitness() for x in self._population])
            else:
                parents = self._pick_tournament(len(self._population) // 2)
            # potentially crossover the 2 parents
            if random() < self._crossover_chance:
                new_population.extend(parents[0].crossover(parents[1]))
            else:
                new_population.extend(parents)
        # if we had an odd number, we'll have 1 extra, so we remove it
        if len(new_population) > len(self._population):
            new_population.pop()
        self._population = new_population # replace reference

    # With _mutation_chance probability mutate each individual
    def _mutate(self) -> None:
        for individual in self._population:
            if random() < self._mutation_chance:
                individual.mutate()

    # Run the genetic algorithm for max_generations iterations
    # and return the best individual found
    def run(self) -> C:
        best: C = max(self._population, key=self._fitness_key)
        for generation in range(self._max_generations):
            # early exit if we beat threshold
            if best.fitness() >= self._threshold:
                return best
            print(f"Generation {generation} Best {best.fitness()} Avg {mean(map(self._fitness_key, self._population))}")
            self._reproduce_and_replace()
            self._mutate()
            highest: C = max(self._population, key=self._fitness_key)
            if highest.fitness() > best.fitness():
                best = highest # found a new best
        return best # best we found in max_generations


"""求解方程示例"""
class SimpleEquation:
    pass

class SimpleEquation(Chromosome):
    def __init__(self, x: int, y: int) -> None:
        self.x: int = x
        self.y: int = y

    def fitness(self) -> float: # 6x - x^2 + 4y - y^2
        return 6 * self.x - self.x * self.x + 4 * self.y - self.y * self.y

    @classmethod
    def random_instance(cls) -> SimpleEquation:
        return SimpleEquation(randrange(100), randrange(100))

    def crossover(self, other: SimpleEquation) -> Tuple[SimpleEquation, SimpleEquation]:
        child1: SimpleEquation = deepcopy(self)
        child2: SimpleEquation = deepcopy(other)
        child1.y = other.y
        child2.y = self.y
        return child1, child2

    def mutate(self) -> None:
        if random() > 0.5: # mutate x
            if random() > 0.5:
                self.x += 1
            else:
                self.x -= 1
        else: # otherwise mutate y
            if random() > 0.5:
                self.y += 1
            else:
                self.y -= 1

    def __str__(self) -> str:
        return f"X: {self.x} Y: {self.y} Fitness: {self.fitness()}"


if __name__ == "__main__":
    initial_population: List[SimpleEquation] = [SimpleEquation.random_instance() for _ in range(20)]
    ga: GeneticAlgorithm[SimpleEquation] = GeneticAlgorithm(initial_population=initial_population, threshold=13.0, max_generations = 100, mutation_chance = 0.1, crossover_chance = 0.7)
    result: SimpleEquation = ga.run()
    print(result)
