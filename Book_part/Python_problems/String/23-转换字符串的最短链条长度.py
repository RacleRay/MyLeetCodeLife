"""起始字符串每次只能变动一个char，且变换后的string必须在规定集合内，达到目标string为止"""

from collections import deque


def acceptable(str1, str2):
    assert len(str1) == len(str2)

    length = len(str1)
    diff = 0
    for (char1, char2) in zip(str1, str2):
        if char1 != char2:
            diff += 1
            if diff > 1:
                return False
    return diff == 1


def shortestPathLen(start, target, choiceSet):
    """BFS, 包含开头和结尾"""
    path = deque()
    path.append(start)
    shortestLen = 1
    while len(path) > 0:
        curState = path.popleft()
        for option in choiceSet:
            if acceptable(option, curState):
                shortestLen += 1
                path.append(option)
                choiceSet.remove(option)
                if option == target:
                    return shortestLen
    return None


if __name__ == "__main__":
    choiceSet = []
    choiceSet.append("pooN")
    choiceSet.append("pbcc")
    choiceSet.append("zamc")
    choiceSet.append("poIc")
    choiceSet.append("pbca")
    choiceSet.append("pbIc")
    choiceSet.append("poIN")

    start = "TooN"
    target = "pbca"
    print(shortestPathLen(start, target, choiceSet))