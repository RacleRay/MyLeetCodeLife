def countSort(alist, maximum):
    """
    maximum: the maximum of alist elements.
    """
    length = len(alist)
    count_list = [0] * (maximum + 1) # include '0'
    sorted_list = [0] * length

    # count each value element
    for i in range(length):
        count_list[alist[i]] += 1

    # cumulate count of elements, asending as index.
    for i in range(1, maximum + 1):
        count_list[i] = count_list[i] + count_list[i - 1]

    for i in range(length):
        first_index_of_value = count_list[alist[i]] - 1
        sorted_list[first_index_of_value] = alist[i]
        count_list[alist[i]] -= 1

    return sorted_list