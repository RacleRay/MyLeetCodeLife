//
// Created by Raclerrr on 2020/3/25.
//

#ifndef ALGO_ASTAR_H
#define ALGO_ASTAR_H

#include <list>
#include <algorithm>
#include <iostream>

/*point in map*/
class Point {
public:
    Point(int a = 0, int b = 0) { x = a, y = b; }

    bool operator==(const Point &o) { return o.x == x && o.y == y; }

    Point operator+(const Point &o) { return Point(x + o.x, y + o.y); }

    int x, y;
};


class Map {
public:
    Map() {
        char t[8][8] = {
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 1, 1, 0},
                {0, 0, 1, 0, 0, 0, 1, 0},
                {0, 0, 1, 0, 0, 0, 1, 0},
                {0, 0, 1, 1, 1, 1, 1, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0}
        };
        w = h = 8;
        for (int r = 0; r < h; r++)
            for (int c = 0; c < w; c++)
                m[c][r] = t[r][c];
    }

    int operator()(int x, int y) { return m[x][y]; }

    char m[8][8];
    int w, h;
};

/*node in open list and closed list*/
class Node_ {
public:
    bool operator==(const Node_ &o) { return pos == o.pos; }

    bool operator==(const Point &o) { return pos == o; }

    bool operator<(const Node_ &o) { return dist + cost < o.dist + o.cost; }

    Point pos, parent;
    int dist, cost;  // dist: to end; cost: from begin.
};


class AStar {
public:
    Map map;
    Point start, end;
    Point neighbours[8];
    std::list<Node_> open;  // to be travelled point
    std::list<Node_> closed;  // included point

    // eight directions
    AStar() {
        neighbours[0] = Point(-1, -1);
        neighbours[1] = Point(1, -1);
        neighbours[2] = Point(-1, 1);
        neighbours[3] = Point(1, 1);
        neighbours[4] = Point(0, -1);
        neighbours[5] = Point(-1, 0);
        neighbours[6] = Point(0, 1);
        neighbours[7] = Point(1, 0);
    }

    int calDist(Point &p) {
        // estimate the distance to end, using Euclidean distance
        int x = end.x - p.x, y = end.y - p.y;
        return (x * x + y * y);
    }

    bool isValid(Point &p) {
        return p.x > -1 && p.y > -1 && p.x < map.w && p.y < map.h;
    }

    // check whether node with smaller total cost in open or closed list
    bool exists(Point &p, int cost) {
        std::list<Node_>::iterator i;
        i = std::find(closed.begin(), closed.end(), p);
        if (i != closed.end()) {
            if ((*i).cost + (*i).dist < cost) return true;
            else {
                closed.erase(i);
                return false;
            }
        }
        i = std::find(open.begin(), open.end(), p);
        if (i != open.end()) {
            if ((*i).cost + (*i).dist < cost) return true;
            else {
                open.erase(i);
                return false;
            }
        }
        return false;
    }

    bool fillOpen(Node_ &n) {
        int stepCost, nextCost, dist;
        Point neighbour;
        for (int x = 0; x < 8; x++) {
            stepCost = 1;
            neighbour = n.pos + neighbours[x];
            if (neighbour == end) return true;

            if (isValid(neighbour) && map(neighbour.x, neighbour.y) != 1) {
                nextCost = stepCost + n.cost;
                dist = calDist(neighbour);
                if (!exists(neighbour, nextCost + dist)) {
                    Node_ m;
                    m.cost = nextCost;
                    m.dist = dist;
                    m.pos = neighbour;
                    m.parent = n.pos;
                    open.push_back(m);
                }
            }
        }
        return false;
    }

    bool search(Point &s, Point &e, Map &m) {
        Node_ n;
        end = e;
        start = s;
        map = m;
        n.cost = 0;
        n.pos = s;
        n.parent = 0;
        n.dist = calDist(s);

        open.push_back(n);
        while (!open.empty()) {
            open.sort();
            Node_ n = open.front();
            open.pop_front();
            closed.push_back(n);
            if (fillOpen(n)) return true;
        }
        return false;
    }

    int path(std::list<Point> &path) {
        path.push_front(end);
        int cost = 1 + closed.back().cost;
        path.push_front(closed.back().pos);
        Point parent = closed.back().parent;
        // travel nodes reversely
        for (std::list<Node_>::reverse_iterator i = closed.rbegin(); i != closed.rend(); i++) {
            if ((*i).pos == parent && !((*i).pos == start)) {
                path.push_front((*i).pos);
                parent = (*i).parent;
            }
        }
        path.push_front(start);
        return cost;
    }
};

#endif //ALGO_ASTAR_H
