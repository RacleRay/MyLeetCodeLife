"""顺序无关，顺出显示为升序"""
import pysnooper


result = []

def find(total, start, tempsum, templist):
    if tempsum == total:
        result.append(templist[:])  # python引用机制，必须要加[:]创建新对象
        return
    if tempsum > total:
        return
    for i in range(start, total + 1):
        templist.append(i)
        find(total, i, tempsum + i, templist)
        templist.pop()  # 回溯


def getResult(total):
    tempsum = 0
    templist = []
    find(total, 1, tempsum, templist)


if __name__ == "__main__":
    getResult(4)
    print(result)