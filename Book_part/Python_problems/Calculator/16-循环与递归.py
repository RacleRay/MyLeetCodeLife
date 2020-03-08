def prints(n):
    if n > 0:
        prints(n - 1)
        print(n)


if __name__ == "__main__":
    print(prints(10))
