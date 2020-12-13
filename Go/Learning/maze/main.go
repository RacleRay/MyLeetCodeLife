package main

import (
	"fmt"
	"os"
)

type Point struct {
	i, j int
}

func (p Point) add(another Point) Point {
	return Point{p.i + another.i, p.j + another.j}
}

// 检查位置合法性: return 是否使用[0或者int value], 是否在maze范围内[true or false]
func (p Point) at(grid [][]int) (int, bool) {
	if p.i < 0 || p.i >= len(grid) {
		return 0, false
	}

	if p.j < 0 || p.j >= len(grid[p.i]) {
		return 0, false
	}

	return grid[p.i][p.j], true
}

var directions = [4]Point{
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1},
}

func readMaze(filename string) [][]int {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	var row, col int
	fmt.Fscanf(file, "%d %d", &row, &col)

	maze := make([][]int, row)
	for i := range maze {
		maze[i] = make([]int, col)
		for j := range maze[i] {
			fmt.Fscanf(file, "%d", &maze[i][j])
		}
	}
	return maze
}

func walk(maze [][]int, start Point, end Point) [][]int {
	steps := make([][]int, len(maze))
	for i := range steps {
		steps[i] = make([]int, len(maze[i]))
	}

	queue := []Point{start}
	steps[start.i][start.j] = 1
	for len(queue) > 0 {
		cur := queue[0]
		queue = queue[1:]
		if cur == end {
			break
		}
		for _, direction := range directions {
			next := cur.add(direction)
			// check if in maze
			if val, ok := next.at(maze); !ok || val == 1 {
				continue
			}
			// check if have been used
			if val, ok := next.at(steps); !ok || val != 0 {
				continue
			}
			curStep, _ := cur.at(steps)
			steps[next.i][next.j] = curStep + 1
			queue = append(queue, next)
		}
	}
	return steps
}

func main() {
	maze := readMaze("maze.in")
	steps := walk(maze, Point{0, 0}, Point{len(maze) - 1, len(maze[0]) - 1})

	for _, row := range steps {
		for _, val := range row {
			fmt.Printf("%3d", val)
		}
		fmt.Println()
	}
}
