#/*************************************************************************
#    > File Name: C59_线段压缩.py
#    > Author: racle
#    > Mail: racleray@qq.com
#    > Created Time: 
# ************************************************************************/
# coding=utf-8


nums = list(map(int, input().split()))

def getResult():
    ans = []

    pre_x = nums[0]
    pre_y = nums[1]

    pre_dir_x = 0
    pre_dir_y = 0

    for i in range(2, len(nums), 2):
        cur_x = nums[i]
        cur_y = nums[i + 1]

        offset_x = cur_x - pre_x
        offset_y = cur_y - pre_y

        base = max(abs(offset_x), abs(offset_y))
        direct_x = offset_x // base
        direct_y = offset_y // base

        if direct_x != pre_dir_x or direct_y != pre_dir_y:
            ans.extend([pre_x, pre_y])

        pre_x = cur_x
        pre_y = cur_y

        pre_dir_x = direct_x
        pre_dir_y = direct_y

    ans.extend([pre_x, pre_y])

    return " ".join(map(str, ans))




if __name__=='__main__':
    print(getResult())
