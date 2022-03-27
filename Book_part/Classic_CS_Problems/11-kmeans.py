from math import sqrt
from typing import TypeVar, Generic, List, Sequence, Iterable, Tuple, Iterator
from copy import deepcopy
from functools import partial
from random import uniform
from statistics import mean, pstdev
from dataclasses import dataclass


class DataPoint:
    ...

class DataPoint:
    def __init__(self, initial: Iterable[float]) -> None:
        self._originals: Tuple[float, ...] = tuple(initial)
        self.dimensions: Tuple[float, ...] = tuple(initial)

    @property
    def num_dimensions(self) -> int:
        return len(self.dimensions)

    def distance(self, other: DataPoint) -> float:
        combined: Iterator[Tuple[float, float]] = zip(self.dimensions, other.dimensions)
        differences: List[float] = [(x - y) ** 2 for x, y in combined]
        return sqrt(sum(differences))

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, DataPoint):
            return NotImplemented
        return self.dimensions == other.dimensions

    def __repr__(self) -> str:
        return self._originals.__repr__()


Point = TypeVar('Point', bound=DataPoint)


def zscores(original: Sequence[float]) -> List[float]:
    avg: float = mean(original)
    std: float = pstdev(original)
    if std == 0: # return all zeros if there is no variation
        return [0] * len(original)
    return [(x - avg) / std for x in original]

class KMeans(Generic[Point]):
    ...

class KMeans(Generic[Point]):
    @dataclass
    class Cluster:
        points: List[Point]
        centroid: DataPoint

    def __init__(self, k: int, points: List[Point]) -> None:
        if k < 1: # k-means can't do negative or zero clusters
            raise ValueError("k must be >= 1")
        self._points: List[Point] = points
        self._zscore_normalize()
        # initialize empty clusters with random centroids
        self._clusters: List[KMeans.Cluster] = []
        for _ in range(k):
            rand_point: DataPoint = self._random_point()
            cluster: KMeans.Cluster = KMeans.Cluster([], rand_point)
            self._clusters.append(cluster)

    @property
    def _centroids(self) -> List[DataPoint]:
        return [x.centroid for x in self._clusters]

    def _dimension_slice(self, dimension: int) -> List[float]:
        return [x.dimensions[dimension] for x in self._points]

    def _zscore_normalize(self) -> None:
        zscored: List[List[float]] = [[] for _ in range(len(self._points))]
        for dimension in range(self._points[0].num_dimensions):
            dimension_slice: List[float] = self._dimension_slice(dimension)
            for index, zscore in enumerate(zscores(dimension_slice)):
                zscored[index].append(zscore)
        for i in range(len(self._points)):
            self._points[i].dimensions = tuple(zscored[i])

    def _random_point(self) -> DataPoint:
        rand_dimensions: List[float] = []
        for dimension in range(self._points[0].num_dimensions):
            values: List[float] = self._dimension_slice(dimension)
            rand_value: float = uniform(min(values), max(values))
            rand_dimensions.append(rand_value)
        return DataPoint(rand_dimensions)

    # Find the closest cluster centroid to each point and assign the point to that cluster
    def _assign_clusters(self) -> None:
        for point in self._points:
            closest: DataPoint = min(self._centroids, key=partial(DataPoint.distance, point))
            idx: int = self._centroids.index(closest)
            cluster: KMeans.Cluster = self._clusters[idx]
            cluster.points.append(point)

    # Find the center of each cluster and move the centroid to there
    def _generate_centroids(self) -> None:
        for cluster in self._clusters:
            if len(cluster.points) == 0: # keep the same centroid if no points
                continue
            means: List[float] = []
            for dimension in range(cluster.points[0].num_dimensions):
                dimension_slice: List[float] = [p.dimensions[dimension] for p in cluster.points]
                means.append(mean(dimension_slice))
            cluster.centroid = DataPoint(means)

    def run(self, max_iterations: int = 100) -> List[KMeans.Cluster]:
        for iteration in range(max_iterations):
            for cluster in self._clusters: # clear all clusters
                cluster.points.clear()
            self._assign_clusters() # find cluster each point is closest to
            old_centroids: List[DataPoint] = deepcopy(self._centroids) # record
            self._generate_centroids() # find new centroids
            if old_centroids == self._centroids: # have centroids moved?
                print(f"Converged after {iteration} iterations")
                return self._clusters
        return self._clusters


if __name__ == "__main__":
    class Governor(DataPoint):
        def __init__(self, longitude: float, age: float, state: str) -> None:
            super().__init__([longitude, age])
            self.longitude = longitude
            self.age = age
            self.state = state

        def __repr__(self) -> str:
            return f"{self.state}: (longitude: {self.longitude}, age: {self.age})"

    governors: List[Governor] = [Governor(-86.79113, 72, "Alabama"), Governor(-152.404419, 66, "Alaska"),
                 Governor(-111.431221, 53, "Arizona"), Governor(-92.373123, 66, "Arkansas"),
                 Governor(-119.681564, 79, "California"), Governor(-105.311104, 65, "Colorado"),
                 Governor(-72.755371, 61, "Connecticut"), Governor(-75.507141, 61, "Delaware"),
                 Governor(-81.686783, 64, "Florida"), Governor(-83.643074, 74, "Georgia"),
                 Governor(-157.498337, 60, "Hawaii"), Governor(-114.478828, 75, "Idaho"),
                 Governor(-88.986137, 60, "Illinois"), Governor(-86.258278, 49, "Indiana"),
                 Governor(-93.210526, 57, "Iowa"), Governor(-96.726486, 60, "Kansas"),
                 Governor(-84.670067, 50, "Kentucky"), Governor(-91.867805, 50, "Louisiana"),
                 Governor(-69.381927, 68, "Maine"), Governor(-76.802101, 61, "Maryland"),
                 Governor(-71.530106, 60, "Massachusetts"), Governor(-84.536095, 58, "Michigan"),
                 Governor(-93.900192, 70, "Minnesota"), Governor(-89.678696, 62, "Mississippi"),
                 Governor(-92.288368, 43, "Missouri"), Governor(-110.454353, 51, "Montana"),
                 Governor(-98.268082, 52, "Nebraska"), Governor(-117.055374, 53, "Nevada"),
                 Governor(-71.563896, 42, "New Hampshire"), Governor(-74.521011, 54, "New Jersey"),
                 Governor(-106.248482, 57, "New Mexico"), Governor(-74.948051, 59, "New York"),
                 Governor(-79.806419, 60, "North Carolina"), Governor(-99.784012, 60, "North Dakota"),
                 Governor(-82.764915, 65, "Ohio"), Governor(-96.928917, 62, "Oklahoma"),
                 Governor(-122.070938, 56, "Oregon"), Governor(-77.209755, 68, "Pennsylvania"),
                 Governor(-71.51178, 46, "Rhode Island"), Governor(-80.945007, 70, "South Carolina"),
                 Governor(-99.438828, 64, "South Dakota"), Governor(-86.692345, 58, "Tennessee"),
                 Governor(-97.563461, 59, "Texas"), Governor(-111.862434, 70, "Utah"),
                 Governor(-72.710686, 58, "Vermont"), Governor(-78.169968, 60, "Virginia"),
                 Governor(-121.490494, 66, "Washington"), Governor(-80.954453, 66, "West Virginia"),
                 Governor(-89.616508, 49, "Wisconsin"), Governor(-107.30249, 55, "Wyoming")]
    kmeans: KMeans[Governor] = KMeans(2, governors)
    gov_clusters: List[KMeans.Cluster] = kmeans.run()
    for index, cluster in enumerate(gov_clusters):
        print(f"Cluster {index}: {cluster.points}\n")
