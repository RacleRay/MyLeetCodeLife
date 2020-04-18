import argparse
from collections import Counter, defaultdict
import heapq
import numpy as np
import os
import ray


"""
Ray:
    - GlobalScheduler：Master上启动了一个全局调度器，用于接收本地调度器提交
的任务，并将任务分发给合适的本地任务调度器执行。
    - RedisServer：Master上启动了一到多个RedisServer用于保存分布式任务的状
态信息（ControlState），包括对象机器的映射、任务描述、任务debug信息等。
    - LocalScheduler：每个Slave上启动了一个本地调度器，用于提交任务到全局调
度器，以及分配任务给当前机器的Worker进程。
    - Worker：每个Slave上可以启动多个Worker进程执行分布式任务，并将计算结果
存储到ObjectStore。
    - ObjectStore：每个Slave上启动了一个ObjectStore存储只读数据对象，Worker
可以通过共享内存的方式访问这些对象数据，这样可以有效地减少内存拷贝和
对象序列化成本。ObjectStore底层由Apache Arrow实现。
    - Plasma：每个Slave上的ObjectStore都由一个名为Plasma的对象管理器进行管
理，它可以在Worker访问本地ObjectStore上不存在的远程数据对象时，主动拉
取其它Slave上的对象数据到当前机器。
"""


parser = argparse.ArgumentParser()
parser.add_argument("--num-mappers",
                    help="number of mapper actors used", default=3, type=int)
parser.add_argument("--num-reducers",
                    help="number of reducer actors used", default=4, type=int)


@ray.remote
class Mapper(object):
    def __init__(self, content_stream):
        self.content_stream = content_stream
        self.num_articles_processed = 0
        self.articles = []
        self.word_counts = []

    def get_new_article(self):
        article = self.content_stream.next()
        # Count the words and store the result.
        self.word_counts.append(Counter(article.split(" ")))
        self.num_articles_processed += 1

    def get_range(self, article_index, keys):
        """keys: list of 2 chars
        article_index：当前mapper处理的文章index，需要与GlobalScheduler中任务参数进行通信，
            保证当前article在整个处理序列中处于article_index的位置"""
        # Process more articles if this Mapper hasn't processed enough yet.
        while self.num_articles_processed < article_index + 1:
            self.get_new_article()
        # Return the word counts from within a given character range.
        return [(k, v) for k, v in self.word_counts[article_index].items()
                if len(k) >= 1 and k[0] >= keys[0] and k[0] <= keys[1]]


@ray.remote
class Reducer(object):
    def __init__(self, keys, *mappers):
        "针对不同范围的开头字母区间，进行reduce"
        self.mappers = mappers
        self.keys = keys

    def next_reduce_result(self, article_index):
        word_count_sum = defaultdict(lambda: 0)
        # Get the word counts for this Reducer's keys from all of the Mappers
        # and aggregate the results.
        count_ids = [mapper.get_range.remote(article_index, self.keys)
                                   for mapper in self.mappers]
        # From many Mappers
        for count_id in count_ids:
            for k, v in ray.get(count_id):
                word_count_sum[k] += v
        return word_count_sum


def get_content(file, floder='/data/'):
    file = floder + file
    f = open(file, 'r')
    return f.read()


class Stream(object):
    "数据流生成"
    def __init__(self, max, folder):
        """max: 最大提取文件数量
               folder: 文件夹名称
        """
        self.index = 0
        self.max = max
        self.folder = folder
        self.g = None

    def init(self):
        self.g = self.content()

    def file(self):
        return f"wiki_{0}{self.index}" if self.index < 10 else f"wiki_{self.index}"

    def content(self):
        while self.index < self.max:
            yield get_content(self.file(), self.folder)
            self.index += 1

    def next(self):
        "生成器"
        if not self.g:
            self.init()
        return next(self.g)


if __name__ == "__main__":
    MAX = 10
    args = parser.parse_args()

    ray.init()

    # Create one streaming source of articles per mapper.
    directory = os.path.dirname(os.path.realpath(__file__))
    streams = []
    folders = ['/data/AA/', '/data/AB/', '/data/AC/']
    for i in range(args.num_mappers):
        streams.append(Stream(MAX, folders[i % len(folders)]))

    # Partition the keys among the reducers.
    chunks = np.array_split([chr(i) for i in range(ord("a"), ord("z") + 1)],
                                                      args.num_reducers)
    keys = [[chunk[0], chunk[-1]] for chunk in chunks]

    # Create a number of mappers.
    mappers = [Mapper.remote(stream) for stream in streams]

    # Create a number of reduces, each responsible for a different range of
    # keys. This gives each Reducer actor a handle to each Mapper actor.
    reducers = [Reducer.remote(key, *mappers) for key in keys]


    # Most frequent 10 words.
    article_index = 0
    while True:
        print("article index = {}".format(article_index))
        wordcounts = {}
        counts = ray.get([reducer.next_reduce_result.remote(article_index)
                                          for reducer in reducers])
        for count in counts:
            wordcounts.update(count)
        most_frequent_words = heapq.nlargest(10,
                                                                                            wordcounts,
                                                                                            key=wordcounts.get)
        for word in most_frequent_words:
            print("  ", word, wordcounts[word])
        article_index += 1