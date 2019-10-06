#!/usr/bin/python3

import sys, threading

sys.setrecursionlimit(10**7) # max depth of recursion
threading.stack_size(2**25)  # new thread will get stack of such size


def IsBinarySearchTree(tree):

  if len(tree) <= 1:
    return True

  prev = None  # 记录中序遍历顺序的当前节点的前一个节点

  def _isbst(root):
    if root == -1:
      return True

    nonlocal prev
    if _isbst(tree[root][1]) is False:  # 左子树
      return False

    if prev is not None and tree[prev][0] > tree[root][0]:
      return False

    prev = root

    return _isbst(tree[root][2])

  return _isbst(0)


def main():
  nodes = int(sys.stdin.readline().strip())
  tree = []
  for i in range(nodes):
    tree.append(list(map(int, sys.stdin.readline().strip().split())))
  if IsBinarySearchTree(tree):
    print("CORRECT")
  else:
    print("INCORRECT")

threading.Thread(target=main).start()
