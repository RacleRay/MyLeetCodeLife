"""
假设小明参与一个游戏，面对三个关闭的门，其中一个后面有篮球🏀，他想要得到这个篮球。
他可以选择两次，第一次选择一个门，此时小白会从剩下的两扇门中打开一扇（只会打开没有球的）；
第二次，小明可以选择换到另一扇或不换。
问，小明第二次换或者不换，哪一个得到球的概率更大。
"""

import random
import sys


def gameplay(choice: bool) -> bool:
    bonus_door = random.randint(1, 3)
    first_chosen = random.randint(1, 3)

    if (bonus_door == first_chosen):
        return not choice
    else:
        return choice


def main(n_simulation: int) -> None:
    n_win = 0
    choose_change = True
    for i in range(n_simulation):
        if gameplay(choose_change):
            n_win += 1
    sys.stdout.write("第二次选择换门： %.4f \n" % (n_win / n_simulation))

    n_win = 0
    choose_change = False
    for i in range(n_simulation):
        if gameplay(choose_change):
            n_win += 1
    sys.stdout.write("第二次选择不换门： %.4f \n" % (n_win / n_simulation))

    return

if __name__ == "__main__":
    main(10000)