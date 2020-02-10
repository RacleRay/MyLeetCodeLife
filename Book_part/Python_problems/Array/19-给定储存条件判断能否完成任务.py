# python3


"""根据需要的临时空间大小，顺序处理任务"""


def bubbleSort(RUN, OUT):
    """RUN -- 执行任务需要的空间；
    OUT -- 储存结果需要的空间
    RUN[i] > OUT[i]
    """
    if len(RUN) != len(OUT):
        return
    LENGTH = len(RUN)
    i = 0
    while i < LENGTH - 1:
        j = LENGTH - 1
        while j > i:
            if RUN[j] - OUT[j] > RUN[j - 1] - OUT[j - 1]:
                RUN[j], RUN[j - 1] = RUN[j - 1], RUN[j]
                OUT[j], OUT[j - 1] = OUT[j - 1], OUT[j]
            j -= 1
        i += 1


def schedule(RUN, OUT, MEMO):
    """MEMO -- 可用空间单位数量"""
    bubbleSort(RUN, OUT)

    left_memo = MEMO
    LEN = len(RUN)

    i = 0
    while i < LEN:
        if left_memo < RUN[i]:
            return False
        else:
            left_memo -= OUT[i]
        i += 1

    return True


if __name__ == "__main__":
    R = [10, 15, 23, 20, 6, 9, 7, 16]
    O = [2, 7, 8, 4, 5, 8, 6, 8]
    N = len(R)
    MEMO = 50

    result = schedule(R, O, MEMO)
    if result:
        print("Result R is: ", R)
        print("Result O is: ", O)
