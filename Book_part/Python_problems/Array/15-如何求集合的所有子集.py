"""已知所有可能元素，求所有 2^n 的子集"""


def getSubset(arr, mask, sub_len):
    """mask -- bitmap, e.g: [0 1 0 0]."""
    length = len(arr)
    if length != sub_len:
        # two possible situations of next length
        mask[sub_len] = 1
        getSubset(arr, mask, sub_len + 1)
        mask[sub_len] = 0
        getSubset(arr, mask, sub_len + 1)
    else:
        print("{ ", end="")
        i = 0
        while i < length:
            if mask[i] == 1:
                print(arr[i], end=" ")
            i += 1
        print("}")


def getSubset2(arr):
    if arr is None:
        return None

    res = []
    res.append(arr[0])
    i = 1
    while i < len(arr):
        length_pre = len(res)
        j = 0
        while j < length_pre:
            res.append(res[j] + arr[i])
            j += 1
        res.append(arr[i])
        i += 1
    res.append("<Empty>")

    return res

if __name__ == "__main__":
    array = ['a', 'b', 'c', 'd']
    mask = [0, 0, 0, 0]
    getSubset(array, mask, 0)

    print(getSubset2(array))