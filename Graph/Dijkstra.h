//
// Created by Raclerrr on 2020/3/26.
//

#ifndef ALGO_DIJKSTRA_H
#define ALGO_DIJKSTRA_H


#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <limits>
#include <set>
#include <utility>
#include <algorithm>
#include <iterator>


typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();

struct neighbor {
    vertex_t target;
    weight_t weight;

    neighbor(vertex_t arg_target, weight_t arg_weight) : target(arg_target), weight(arg_weight) {}
};

typedef std::vector<std::vector<neighbor>> adjacencyList;


void Dijkstra(vertex_t source,
              const adjacencyList &adjacency,
              std::vector<vertex_t> &previous,
              std::vector<weight_t> &min_distance) {
    int n = adjacency.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    std::set<std::pair<weight_t, vertex_t>> vertex_queue;  // self-balance tree
    vertex_queue.insert(std::make_pair(min_distance[source], source));

    while (!vertex_queue.empty()) {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t point = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());
        // visit neighbors
        const std::vector<neighbor> &neighbors = adjacency[point];
        for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end(); ++neighbor_iter) {
            vertex_t neighbor_point = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t dist_through_point = dist + weight;
            if (dist_through_point < min_distance[neighbor_point]) {
                vertex_queue.erase(std::make_pair(min_distance[neighbor_point], neighbor_point));
                min_distance[neighbor_point] = dist_through_point;
                previous[neighbor_point] = point;
                vertex_queue.insert(std::make_pair(min_distance[neighbor_point], neighbor_point));
            }
        }
    }
}


/*Single source and non-negtive weights edge*/
std::list<vertex_t> DijkstraShortestPath(vertex_t vertex, const std::vector<vertex_t>& previous){
    std::list<vertex_t> path;
    for (;vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}


void runDijkstra()
{
    // remember to insert edges both ways for an undirected graph
    adjacencyList adjacency_list(6);
    // 0 = a
    adjacency_list[0].push_back(neighbor(1, 7));
    adjacency_list[0].push_back(neighbor(2, 9));
    adjacency_list[0].push_back(neighbor(5, 14));
    // 1 = b
    adjacency_list[1].push_back(neighbor(0, 7));
    adjacency_list[1].push_back(neighbor(2, 10));
    adjacency_list[1].push_back(neighbor(3, 15));
    // 2 = c
    adjacency_list[2].push_back(neighbor(0, 9));
    adjacency_list[2].push_back(neighbor(1, 10));
    adjacency_list[2].push_back(neighbor(3, 11));
    adjacency_list[2].push_back(neighbor(5, 2));
    // 3 = d
    adjacency_list[3].push_back(neighbor(1, 15));
    adjacency_list[3].push_back(neighbor(2, 11));
    adjacency_list[3].push_back(neighbor(4, 6));
    // 4 = e
    adjacency_list[4].push_back(neighbor(3, 6));
    adjacency_list[4].push_back(neighbor(5, 9));
    // 5 = f
    adjacency_list[5].push_back(neighbor(0, 14));
    adjacency_list[5].push_back(neighbor(2, 2));
    adjacency_list[5].push_back(neighbor(4, 9));

    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;
    Dijkstra(0, adjacency_list, previous, min_distance);
    std::cout << "Distance from 0 to 4: " << min_distance[4] << std::endl;
    std::list<vertex_t> path = DijkstraShortestPath(4, previous);
    std::cout << "Path : ";
    std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;
}

#endif //ALGO_DIJKSTRA_H
