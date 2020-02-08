"""二维方形数组旋转45度，进行显示"""


def rotate(arr):
    size = len(arr)

    # 右上部分：最后一列，第一行开始。不包括第一列
    i = size - 1
    while i > 0:
        row = 0
        col = i
        while col < size:
            print(arr[row][col], end=' ')
            row += 1
            col += 1
        i -= 1
        print()

    # 左下部分，包括对角线
    i = 0
    while i < size:
        row = i
        col = 0
        while row < size:
            print(arr[row][col], end=' ')
            row += 1
            col += 1
        i += 1
        print()


if __name__ == "__main__":
    arr = [[1,2,3],[4,5,6],[7,8,9]]
    rotate(arr)