# python3

from itertools import combinations


def compute_inversions_naive(a):
    number_of_inversions = 0
    for i, j in combinations(range(len(a)), 2):
        if a[i] > a[j]:
            number_of_inversions += 1
    return number_of_inversions


def compute_inversions(a):
    def _mereSort(a):
        def _merge(A, B):
            if A[-1] < B[0]:
                return 0, A + B

            p_A = p_B = p_C = 0
            C = []
            count = 0
            while p_A < len(A) and p_B < len(B):
                if A[p_A] <= B[p_B]:
                    C.append(A[p_A])
                    p_A += 1
                else:
                    C.append(B[p_B])
                    count += len(A) - p_A  # 右侧全部大于当前的B[p_B]
                    p_B += 1

                p_C += 1
            # 处理剩余
            if p_A < len(A):
                C += A[p_A: ]
            elif p_B < len(B):
                C += B[p_B: ]

            return count, C

        if len(a) == 1:
            return 0, a

        mid = (len(a) - 1) // 2
        res1, A = _mereSort(a[: mid + 1])
        res2, B = _mereSort(a[mid + 1: ])

        res3, C = _merge(A, B)

        # 结果为两个子过程，和当前过程的和
        res = res1 + res2 + res3

        return res, C

    res, C = _mereSort(a)
    return res


if __name__ == '__main__':
    input_n = int(input())
    elements = list(map(int, input().split()))
    assert len(elements) == input_n
    print(compute_inversions(elements))
