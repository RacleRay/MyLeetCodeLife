

"LintCode 1852. 最终优惠价"

class Solution:
    def finalDiscount(self, prices):
        stack = []
        results = list(prices)

        for i in range(len(prices)):
            while stack and prices[stack[-1]] >= prices[i]:
                results[stack[-1]] = prices[stack[-1]] - prices[i]
                stack.pop(-1)
            stack.append(i)

        return results

