# python3


"""重复数字的高效排序"""


# Method1: AVL Tree

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1
        self.count = 1

class Sort:
    def sort(self, arr):
        root = None
        length = len(arr)
        for data in arr:
            root = self.insert(root, data)

        self.inorder(arr, root, 0)

    def insert(self, root, data):
        """重复数组节点，累计count"""
        if root is None:
            return Node(data)

        if data == root.data:
            root.count += 1
            return root

        if data < root.data:
            root.left = self.insert(root.left, data)
        else:
            root.right = self.insert(root.right, data)

        root.height = max(self.getHeight(root.left), self.getHeight(root.right)) + 1
        balance_factor = self.getBalance(root)
        if balance_factor > 1 and data < root.left.data:
            return self.rightRotate(root)
        elif balance_factor < -1 and data > root.right.data:
            return self.leftRotate(root)
        elif balance_factor > 1 and data > root.left.data:
            root.left = self.leftRotate(root.left)
            return self.rightRotate(root)
        elif balance_factor < -1 and data < root.right.data:
            root.right = self.rightRotate(root.right)
            return self.leftRotate(root)

        return root

    @staticmethod
    def getHeight(node):
        return node.height if node is not None else 0

    def getBalance(self, node):
        if node is None:
            return 0
        return self.getHeight(node.left) - self.getHeight(node.right)

    def rightRotate(self, root):
        left = root.left
        right_of_left = left.right

        left.right = root
        root.left = right_of_left

        root.height = max(self.getHeight(root.left), self.getHeight(root.right)) + 1
        left.height = max(self.getHeight(left.left), self.getHeight(left.right)) + 1

        return left

    def leftRotate(self, root):
        right = root.right
        left_of_right = right.left

        right.left = root
        root.right = left_of_right

        root.height = max(self.getHeight(root.left), self.getHeight(root.right)) + 1
        right.height = max(self.getHeight(right.left), self.getHeight(right.right)) + 1

        return right

    def inorder(self, arr, root, idx):
        if root is not None:
            idx = self.inorder(arr, root.left, idx)
            arr[idx: idx + root.count] = [root.data for _ in range(root.count)]
            idx += root.count
            idx = self.inorder(arr, root.right, idx)
        return idx


# Method2: Hash

def sort(arr):
    dic_count = {}
    for data in arr:
        dic_count[data] = dic_count.setdefault(data, 0) + 1

    a = dic_count.keys
    keys = sorted(dic_count.keys())
    idx = 0
    for key in keys:
        arr[idx: idx + dic_count[key]] = [key for _ in range(dic_count[key])]
        idx += dic_count[key]

    return arr

if __name__ == "__main__":
    arr = [15, 12, 15, 15, 2, 2, 2, 12, 3, 3, 3]
    solution = Sort()
    solution.sort(arr)
    print(arr)

    arr = [15, 12, 15, 15, 2, 2, 2, 12, 3, 3, 3]
    arr = sort(arr)
    print(arr)