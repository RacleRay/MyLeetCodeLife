"""
设计一个算法，找出只含素因子2，3，5 的第n小的数
"""

import heapq


def ugly_number(n):
    # 最小堆 + set
    heap = [1]
    seen = set([1])

    curr_ugly = 1
    for _ in range(n):
        curr_ugly = heapq.heapop(heap)
        for factor in [2, 3, 5]:
            new_ugly= curr_ugly * factor
            if new_ugly not in seen:
                seen.add(new_ugly)
                heapq.heappush(heap, new_ugly)

    return curr_ugly


def ugly_number_dp(n):
    dp = [0] * n
    dp[0] = 1
    m2, m3, m5 = 0, 0, 0
    for i in range(1, n):
        dp[i] = min(2 * dp[m2], 3 * dp[m3], 5 * dp[m5])
        if dp[i] == 2 * dp[m2]:
            m2 += 1
        if dp[i] == 3 * dp[m3]:
            m3 += 1
        if dp[i] == 5 * dp[m5]:
            m5 += 1
    return dp[n - 1]