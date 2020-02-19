def get_possibility(disk_list, partition_list):
    disk_idx = 0
    for part in partition_list:
        while disk_idx < len(disk_list) and part > disk_list[disk_idx]:
            disk_idx += 1
        if disk_idx >= len(disk_list):
            return False
        disk_list[disk_idx] -= part
    return True


if __name__ == "__main__":
    disk_list = [120, 120, 120]
    partition_list = [60, 60, 80, 80, 20]
    print(get_possibility(disk_list, partition_list))