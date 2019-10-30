# python3

EPS = 1e-6
PRECISION = 20

class Equation:
    def __init__(self, a, b):
        self.a = a
        self.b = b

class Position:
    def __init__(self, column, row):
        self.column = column
        self.row = row

def ReadEquation():
    size = int(input())
    a = []
    b = []
    for row in range(size):
        line = list(map(float, input().split()))
        a.append(line[:size])
        b.append(line[size])
    return Equation(a, b)

def SelectPivotElement(a, used_rows, used_columns):
    # This algorithm selects the first free element.
    # You'll need to improve it to pass the problem.
    pivot_element = Position(0, 0)
    while used_rows[pivot_element.row]:
        pivot_element.row += 1
    while used_columns[pivot_element.column]:
        pivot_element.column += 1
    while a[pivot_element.row][pivot_element.column] == 0:
        pivot_element.column += 1
    return pivot_element

def SwapLines(a, b, used_rows, pivot_element):
    a[pivot_element.column], a[pivot_element.row] = a[pivot_element.row], a[pivot_element.column]
    b[pivot_element.column], b[pivot_element.row] = b[pivot_element.row], b[pivot_element.column]
    used_rows[pivot_element.column], used_rows[pivot_element.row] = used_rows[pivot_element.row], used_rows[pivot_element.column]
    pivot_element.row = pivot_element.column;

def ProcessPivotElement(a, b, pivot_element):

    # i：pivot所在行，j：pivot所在列
    i, j = pivot_element.row, pivot_element.column

    pivot = a[i][j]

    # pivot所在行，pivot归一
    for i_ in range(len(a[i])):
        a[i][i_] /= pivot
    b[i] /= pivot

    # index：消除行，row：消除行的值, (-row[j]):因子
    for index in range(len(a)):
        # 为0，或者是pivot所在行跳过
        if index != i:
            # index_：column索引
            subtractor = a[index][j]
            for index_ in range(len(a[index])):
                a[index][index_] += a[i][index_] * (-subtractor)

            b[index] += b[i] * (-subtractor)

def MarkPivotElementUsed(pivot_element, used_rows, used_columns):
    used_rows[pivot_element.row] = True
    used_columns[pivot_element.column] = True

def SolveEquation(equation):
    a = equation.a
    b = equation.b
    size = len(a)

    used_columns = [False] * size
    used_rows = [False] * size
    for step in range(size):
        pivot_element = SelectPivotElement(a, used_rows, used_columns)
        SwapLines(a, b, used_rows, pivot_element)
        ProcessPivotElement(a, b, pivot_element)
        MarkPivotElementUsed(pivot_element, used_rows, used_columns)

    return b

def PrintColumn(column):
    size = len(column)
    for row in range(size):
        print("%.20lf" % column[row])

if __name__ == "__main__":
    equation = ReadEquation()
    solution = SolveEquation(equation)
    PrintColumn(solution)
    exit(0)


# 2
# 1 1 3
# 2 3 7

# 4
# 1 0 0 0 1
# 0 1 0 0 5
# 0 0 1 0 4
# 0 0 0 1 3

# 2
# 5 -5 -1
# -1 -2 -1

# 4
# 1 0 0 0 1
# 0 0 0 1 3
# 0 1 0 0 5
# 0 0 1 0 8