# python3
from collections import defaultdict

def solve(inputs_dict):
    reverse_dict = defaultdict()
    for key, value in inputs_dict.items():
        reverse_dict[value] = key

    start = None
    # 找到起点(无环)
    for key, _ in inputs_dict.items():
        if key not in reverse_dict:
            start = key
            break

    if start is None: return None

    # 路径
    next_ = inputs_dict[start]
    print(start + ">" + next_)
    while next_:
        start = next_
        if start in inputs_dict:
            next_ = inputs_dict[start]
            print(">" + next_)
        else:
            break


if __name__ == "__main__":
    inputs_dict = defaultdict()
    inputs_dict["西安"] = "成都"
    inputs_dict["北京"] = "上海"
    inputs_dict["大连"] = "西安"
    inputs_dict["上海"] = "大连"
    solve(inputs_dict)