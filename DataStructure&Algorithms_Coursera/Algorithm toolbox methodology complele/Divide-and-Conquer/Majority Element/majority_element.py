# python3


def majority_element_naive(elements):
    assert len(elements) <= 10 ** 5
    for e in elements:
        if elements.count(e) > len(elements) / 2:
            return 1

    return 0


def majority_element(elements):
    assert len(elements) <= 10 ** 5

    major_candidata = elements[0]
    candidate_count = 1
    for i in elements:
        candidate_count += 1 if i == major_candidata else -1
        if candidate_count == 0:
            major_candidata = i
            candidate_count = 1

    count = 0
    for i in elements:
        if i == major_candidata:
            count += 1
        if count > len(elements) / 2:
            return 1

    return 0


    # def _count(list, element):
    #     count = 0
    #     for i in list:
    #         if i == element:
    #             count += 1
    #     return count
    #
    # def _find_major(elements):
    #     n = len(elements)
    #     if n == 1:
    #         return elements[0]
    #
    #     mid = n // 2
    #     m_left = _find_major(elements[: mid])
    #     m_right = _find_major(elements[mid: ])
    #
    #     if m_left != -1 and m_right != -1:
    #         return m_right if m_left == m_right else -1
    #
    #     if m_left == -1 and m_right != -1:
    #         return m_right if _count(elements, m_right) > n / 2 else -1
    #
    #     if m_left != -1 and m_right == -1:
    #         return m_left if _count(elements, m_left) > n / 2 else -1
    #
    #     return -1
    #
    # return 0 if _find_major(elements) == -1 else 1


if __name__ == '__main__':
    input_n = int(input())
    input_elements = list(map(int, input().split()))
    assert len(input_elements) == input_n
    print(majority_element(input_elements))
