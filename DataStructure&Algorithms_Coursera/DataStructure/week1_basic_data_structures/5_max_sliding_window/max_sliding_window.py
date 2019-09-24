# python3
from collections import deque
import pysnooper

def max_sliding_window_naive(sequence, m):
    maximums = []
    for i in range(len(sequence) - m + 1):
        maximums.append(max(sequence[i:i + m]))

    return maximums

@pysnooper.snoop()
def max_sliding_window(sequence, m):
    assert len(sequence) >= m  # 题目条件
    length = len(sequence)

    if length == 0 or m == 0:
        return None
    if m == 1:
        return sequence

    deq = deque()  # 储存windows元素的index

    def _clear_deque(cur_idx):
        # 出队元素处理
        if deq and deq[0] == cur_idx - m:
            deq.popleft()

        # 删除window中所有比入队元素sequence[i]小的，（index i之前的部分）
        while deq and sequence[cur_idx] > sequence[deq[-1]]:
            deq.pop()

    # 第一个窗口处理
    max_idx = 0
    for cur_idx in range(m):
        _clear_deque(cur_idx)  # 保证最大值index前没有元素
        deq.append(cur_idx)    # 较小元素在窗口内保留
        # 第一个窗口，在range(m)达到窗口大小时才能保证dep[0]为最大的index
        if sequence[cur_idx] > sequence[max_idx]:
            max_idx = cur_idx
    res = [sequence[max_idx]]

    for cur_idx in range(m, length):
        _clear_deque(cur_idx)  # 保证dep[0]前没有元素
        deq.append(cur_idx)    # 较小元素在窗口内保留
        res.append(sequence[deq[0]])

    return res



if __name__ == '__main__':
    n = int(input())
    input_sequence = [int(i) for i in input().split()]
    assert len(input_sequence) == n
    window_size = int(input())

    # input_sequence = [2, 7, 3, 1, 5, 2, 6, 2]
    # window_size = 4
    print(*max_sliding_window(input_sequence, window_size))

