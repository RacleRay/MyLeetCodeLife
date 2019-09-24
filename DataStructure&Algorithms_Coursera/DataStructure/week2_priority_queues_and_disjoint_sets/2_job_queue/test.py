import unittest
from job_queue import *
import random

def read(file):
    with open(file, encoding='utf-8') as f:
        input = f.readline()
        data = f.readline()

    return input, data

# input, data = read(r'.\tests\02')
# input = int(input.strip().split()[0])
# data = list(map(int, data.strip().split()))

input = 10
data = [random.randint(0, 20) for _ in range(100)]

class Check(unittest.TestCase):
    def test_1(self):
        for n_workers, jobs in [(input, data)]:
            self.assertEqual(assign_jobs(n_workers, jobs), assign_jobs_naive(n_workers, jobs))


if __name__ == '__main__':
    unittest.main()
