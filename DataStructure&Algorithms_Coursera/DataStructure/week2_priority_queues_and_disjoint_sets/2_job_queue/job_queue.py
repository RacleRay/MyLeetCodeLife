# python3

from collections import namedtuple
# import pysnooper

AssignedJob = namedtuple("AssignedJob", ["worker", "started_at"])

def assign_jobs_naive(n_workers, jobs):
    # TODO: replace this code with a faster algorithm.
    result = []
    next_free_time = [0] * n_workers
    for job in jobs:
        next_worker = min(range(n_workers), key=lambda w: next_free_time[w])
        result.append(AssignedJob(next_worker, next_free_time[next_worker]))
        next_free_time[next_worker] += job
    return result


def build_heap(heap, size):
    for i in range((size - 1) // 2, -1, -1):
        _shiftdown(i, heap, size)
    return heap


def compare(child, par):
    """child更小"""
    if child.started_at == par.started_at:
        return child.worker < par.worker
    return child.started_at < par.started_at


def _shiftdown(i, heap, size):
        """min heap"""
        min_index = i
        left_child = 2 * i + 1
        right_child = 2 * i + 2

        if left_child <= size and compare(heap[left_child], heap[min_index]):
            min_index = left_child

        if right_child <= size and compare(heap[right_child], heap[min_index]):
            min_index = right_child

        if min_index == i:
            return
        else:
            heap[i], heap[min_index] = heap[min_index], heap[i]
            _shiftdown(min_index, heap, size)


def _extract_min(heap, size):
    res = heap[0]
    heap[0] = heap[size]
    size -= 1
    _shiftdown(0, heap, size)
    return res


def _insert(elem, heap, size):
    size += 1
    heap[size] = elem
    _shiftup(size, heap)


def _shiftup(i, heap):
    parent = (i - 1) // 2
    while i > 0 and compare(heap[i], heap[parent]):
        heap[parent], heap[i] = heap[i], heap[parent]
        i = parent
        parent = (i - 1) // 2

# @pysnooper.snoop(watch='parallel_heap')
def assign_jobs(n_workers, jobs):
    result = []

    init_heap_elems = [AssignedJob(worker, 0) for worker in range(n_workers)]
    # 建立起始堆
    size = n_workers - 1 # 最后一个index
    parallel_heap = build_heap(init_heap_elems, size)

    # 开始流水工作
    for job_time in jobs:
        complete = _extract_min(parallel_heap, size)
        size -= 1

        result.append(complete)

        new_task = AssignedJob(complete.worker, complete.started_at + job_time)
        _insert(new_task, parallel_heap, size)
        size += 1

    return result


def main():
    n_workers, n_jobs = map(int, input().split())
    jobs = list(map(int, input().split()))
    assert len(jobs) == n_jobs

    assigned_jobs = assign_jobs(n_workers, jobs)
    # assigned_jobs_naive = assign_jobs_naive(n_workers, jobs)

    for job in assigned_jobs:
        print(job.worker, job.started_at)

    # for job in assigned_jobs_naive:
    #     print(job.worker, job.started_at)


if __name__ == "__main__":
    main()