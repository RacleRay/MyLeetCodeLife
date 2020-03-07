def compare(a, b):
    # 先假设a较大，再考虑a-b与a-b绝对值的关系
    return int(a - ((a - b) - abs(a - b)) / 2)


if __name__ == "__main__":
    print(compare(1219, 1214))