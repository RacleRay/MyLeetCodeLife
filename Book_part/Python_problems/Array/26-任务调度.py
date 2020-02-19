# python3

"""n个相同任务分配到m个不同的服务器，每个服务器执行时间为t[i]，每个不同。"""

def process_time(t_list, n_task):
    if t_list is None or n_task <= 0:
        return None

    machines_count = len(t_list)
    individual_time = [0] * machines_count

    i = 0
    while i < n_task:  # 每个任务贪心遍历
        minTime = individual_time[0] + t_list[0]
        minIndex = 0
        j = 1
        while j < machines_count:
            if minTime > individual_time[j] + t_list[j]:
                minTime = individual_time[j] + t_list[j]
                minIndex = j
            j += 1
        individual_time[minIndex] += t_list[minIndex]  # 记录当前最优
        i += 1

    return individual_time


if __name__=='__main__':
    t_list = [7, 9, 12]
    n = 8
    schedule = process_time(t_list, n)
    print(schedule)
    print("Total time: ", max(schedule))