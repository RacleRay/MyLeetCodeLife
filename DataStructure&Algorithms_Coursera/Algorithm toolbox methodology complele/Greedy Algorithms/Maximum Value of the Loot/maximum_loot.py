# python3

from sys import stdin


def maximum_loot_value(capacity, weights, prices):
    assert 0 <= capacity <= 2 * 10 ** 6
    assert len(weights) == len(prices)
    assert 1 <= len(weights) <= 10 ** 3
    assert all(0 < w <= 2 * 10 ** 6 for w in weights)
    assert all(0 <= p <= 2 * 10 ** 6 for p in prices)

    unit_price = sorted({p / w: (w, p) for w, p in zip(weights, prices)}.items(),
                        key=lambda x: x[0],
                        reverse=True)
    max_price = 0
    for value_weight in unit_price:
        total_weight = value_weight[1][0]

        if capacity >= total_weight:
            capacity = capacity - total_weight
            max_price += value_weight[1][1]
        else:
            while capacity > 0:
                capacity = capacity - 1
                max_price += value_weight[0]

            # if capacity == 0:
            #     return max_price
            # else:
            #     capacity += value_weight[0]

    return max_price


if __name__ == "__main__":
    data = list(map(int, stdin.read().split()))
    n, input_capacity = data[0:2]  # n, next n line for data
    input_prices = data[2:(2 * n + 2):2]
    input_weights = data[3:(2 * n + 2):2]
    opt_value = maximum_loot_value(input_capacity, input_weights, input_prices)
    print("{:.10f}".format(opt_value))
