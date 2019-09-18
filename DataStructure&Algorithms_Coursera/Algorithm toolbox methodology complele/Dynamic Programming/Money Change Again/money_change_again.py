# python3


def change_naive(money):
    min_coins = float("inf")

    for num1 in range(money + 1):
        for num3 in range(money // 3 + 1):
            for num4 in range(money // 4 + 1):
                if 1 * num1 + 3 * num3 + 4 * num4 == money:
                    min_coins = min(min_coins, num1 + num3 + num4)

    return min_coins


def change(money):
    if money < 3:
        return money

    count = [0, 1, 2, 1]
    for i in range(4, money + 1):
        count[i % 4] = min(count[(i - 1) % 4] + 1, count[(i - 3) % 4] + 1, count[(i - 4) % 4] + 1)

    # count = [0, 1, 2, 1] + [0] * (money - 3)
    # for i in range(4, money + 1):
    #     count[i] = min(count[i - 1] + 1, count[i - 3] + 1, count[i - 4] + 1)

    return count[money % 4]




if __name__ == '__main__':
    amount = int(input())
    print(change(amount))
