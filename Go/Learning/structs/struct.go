package main

import (
	"fmt"
)

type treeNode struct {
	value       int
	left, right *treeNode
}

// 值接收者
func (node treeNode) print() {
	fmt.Print(node.value)
}

// 指针接收者
func (node *treeNode) setValue(value int) {
	if node == nil {
		fmt.Println("Node is nil.")
		return
	}
	node.value = value
}

func createNode(value int) *treeNode {
	return &treeNode{value: value}
}

func main() {
	var root treeNode
	root.setValue(1)
	root.print()

	root = treeNode{value: 3}
	root.left = &treeNode{}
	root.right = &treeNode{5, nil, nil}
	root.left.left = new(treeNode)
	root.left.right = createNode(2)

	pRoot := &root
	pRoot.print()
}
