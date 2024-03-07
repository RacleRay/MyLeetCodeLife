def test():
    try:
        print('1')
        return
        print('2')
    except Exception as e:
        print(e)
    finally:
        print('3')


if __name__ == '__main__':
    test()