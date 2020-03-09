"""100个灯泡，第i轮每隔i个位置对开关进行一次操作，进行了奇数次操作为开启，
偶数次为关闭。100轮之后，亮着几盏灯。"""


def isOddFactors(idx):
    """有奇数个约数的位置，开关奇数次。
    idx -- 灯的位置"""
    count = 0
    i = 1
    while i <= idx:
        if idx % i == 0:
            count += 1
        i += 1
    return True if count % 2 == 1 else False


def lightenedLight(switch_times):
    count = 0
    i = 0
    while i < switch_times:
        if isOddFactors(i + 1):
            print("Light: ", i + 1)
            count += 1
        i += 1
    return count


if __name__ == "__main__":
    count = lightenedLight(100)
    print("Total: ", count)