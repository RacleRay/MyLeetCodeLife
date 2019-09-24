# python3

from collections import namedtuple
# import pysnooper

Request = namedtuple("Request", ["arrived_at", "time_to_process"])
Response = namedtuple("Response", ["was_dropped", "started_at"])


class Buffer:
    def __init__(self, size):
        self.size = size
        self.finish_time = []

    def process(self, request):
        # 处理queue，直到，正在处理的request或者为空
        while len(self.finish_time) > 0 and request.arrived_at >= self.finish_time[-1]:
            self.finish_time.pop()

        if len(self.finish_time) < self.size:  # buffer有空间，enqueue

            if len(self.finish_time) == 0:
                # 为空，就是到达时间
                res =  Response(False, request.arrived_at)
                self.finish_time.insert(0, request.arrived_at + request.time_to_process)
            else:
                # buffer中最近的request的结束时间，是该request开始的时间
                res =  Response(False, self.finish_time[0])
                self.finish_time.insert(0, self.finish_time[0] + request.time_to_process)
            return res

        elif len(self.finish_time) == self.size:  # buffer没有空间，processor is busy, drop
            return Response(True, -1)


def process_requests(requests, buffer):
    responses = []
    for request in requests:
        responses.append(buffer.process(request))
    return responses


def main():
    buffer_size, n_requests = map(int, input().split())
    requests = []
    for _ in range(n_requests):
        arrived_at, time_to_process = map(int, input().split())
        requests.append(Request(arrived_at, time_to_process))

    buffer = Buffer(buffer_size)
    responses = process_requests(requests, buffer)

    for response in responses:
        print(response.started_at if not response.was_dropped else -1)


if __name__ == "__main__":
    main()
