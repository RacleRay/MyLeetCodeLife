from .actor import Actor
from threading import Event


class Result(object):

    def __init__(self):
        self._evt = Event()
        self._result = None

    def set_result(self, value):
        self._result = value
        self._evt.set()  # 当执行完成计算任务时，解除block

    @property
    def result(self):
        self._evt.wait()  # 等待计算结果程序的执行完成，thread block
        return self._result


class Worker(Actor):

    def submit(self, func, *args, **kwargs):
        "注册任务"
        r = Result()
        self.send((func, args, kwargs, r))
        return r

    def run(self):
        "重写actor的run逻辑，执行用户程序"
        while True:
            func, args, kwargs, r = self.recv()
            r.set_result(func(*args, **kwargs))


if __name__ == '__main__':
    worker = Worker()
    worker.start()
    r = worker.submit(pow, 2, 4)
    print('it will not block')
    print(r.result)