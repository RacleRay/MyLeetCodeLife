# python3


def findCommon(arr1, arr2, arr3):
    i, j, k = 0, 0, 0
    len1, len2, len3 = len(arr1), len(arr2), len(arr3)
    result = []

    while i < len1 and j < len2 and k < len3:
        if arr1[i] == arr2[j] and arr2[j] == arr3[k]:
            result.append(arr1[i])
            i += 1; j += 1; k += 1
        elif arr1[i] < arr2[j]:
            i += 1
        elif arr2[j] < arr3[k]:
            j += 1
        else:
            k += 1

    return result


if __name__ == "__main__":
    arr1 = [2, 5, 12, 20, 45, 85]
    arr2 = [16, 19, 20, 85, 200]
    arr3 = [3, 4, 20, 72, 85, 111]
    print("Result is: ", findCommon(arr1, arr2, arr3))