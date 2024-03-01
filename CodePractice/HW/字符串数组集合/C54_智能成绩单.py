class Student:
    def __init__(self, name, rank) -> None:
        self.name = name
        self.rank = rank


n, m = map(int, input().split())

subjects = input().split()
subject_rank_idx = {}
for i in range(m):
    subject_rank_idx[subjects[i]] = i


students = []
for i in range(n):
    tmp = input().split()

    name = tmp[0]
    scores = list(map(int, tmp[1:]))

    rank = []
    rank.extend(scores)
    rank.append(sum(scores))

    students.append(Student(name, rank))


subject = input()
rank_idx = subject_rank_idx.get(subject, m)

students.sort(key=lambda x: (-x.rank[rank_idx], x.name))

print(" ".join(map(lambda x: x.name, students)))