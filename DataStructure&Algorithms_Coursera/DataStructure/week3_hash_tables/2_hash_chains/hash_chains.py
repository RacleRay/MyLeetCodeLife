# python3

class Query:

    def __init__(self, query):
        self.type = query[0]
        if self.type == 'check':
            self.ind = int(query[1])
        else:
            self.s = query[1]


class QueryProcessor:
    _multiplier = 263
    _prime = 1000000007

    def __init__(self, bucket_count):
        self.bucket_count = bucket_count
        # store all strings in one list
        # 注意：不要使用[[]] * bucket_count，这会使内部[]指向同一个对象
        self.m_list = [[] for _ in range(self.bucket_count)]

    def _hash_func(self, s):
        ans = 0
        for c in reversed(s):
            ans = (ans * self._multiplier + ord(c)) % self._prime
        return ans % self.bucket_count

    def write_search_result(self, was_found):
        print('yes' if was_found else 'no')

    def write_chain(self, chain):
        print(' '.join(chain))

    def read_query(self):
        return Query(input().split())

    def process_query(self, query):
        # 找到hash值
        if query.type == "check":
            # use reverse order, because we append strings to the end
            self.write_chain(cur for cur in self.m_list[query.ind])
        else:
            hash_value = self._hash_func(query.s)
            m_list = self.m_list[hash_value]
            if query.type == 'find':
                was_found = False
                for key in m_list:
                    if key == query.s:
                        was_found = True
                self.write_search_result(was_found)

            elif query.type == 'add':
                for key in m_list:
                    if key == query.s:  # 已存在跳过
                        return
                m_list.insert(0, query.s)

            elif query.type == 'del':
                for key in m_list:
                    if key == query.s:
                        m_list.remove(key)
                        return

    def process_queries(self):
        n = int(input())
        for i in range(n):
            self.process_query(self.read_query())

if __name__ == '__main__':
    bucket_count = int(input())
    proc = QueryProcessor(bucket_count)
    proc.process_queries()
