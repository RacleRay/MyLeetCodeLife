# python3


"""有序集合中每个元素表示一段范围"""

class MySet:
    def __init__(self, min_, max_):
        self.min = min_
        self.max = max_


def getIntersection(set1, set2):
    result = []
    i, j = 0, 0
    while i < len(set1) and j < len(set2):
        section1 = set1[i]
        section2 = set2[j]
        if section1.min < section2.min:
            if section1.max < section2.min:
                i += 1
            elif section1.max <= section2.max:
                result.append(MySet(section2.min, section1.max))
                i += 1
            else:
                result.append(MySet(section2.min, section2.max))
                j += 1
        elif section1.min <= section2.max:
            if section1.max <= section2.max:
                result.append(MySet(section1.min, section1.max))
                i += 1
            else:
                result.append(MySet(section1.min, section2.max))
                j += 1
    return result


if __name__ == "__main__":
    set1 = [MySet(4, 8), MySet(9, 13)]
    set2 = [MySet(6, 12)]
    result = getIntersection(set1, set2)
    for s in result:
        print("[{}, {}]".format(s.min, s.max))
