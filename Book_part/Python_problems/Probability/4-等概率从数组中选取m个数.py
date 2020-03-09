import random


def getRandomM(nums, m):
    if nums is None:
        return None
    lens = len(nums)

    assert lens >= m

    i = 0
    while i < m:
        sampleIdx = random.randint(i, lens - 1)
        # 抽取到的元素移动到左侧，不再sample
        nums[sampleIdx], nums[i] = nums[i], nums[sampleIdx]
        i += 1

    return nums[: m]


if __name__ == "__main__":
    nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    m = 5
    print(getRandomM(nums, m))