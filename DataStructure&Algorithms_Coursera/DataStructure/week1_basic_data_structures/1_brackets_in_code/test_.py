import unittest
from check_brackets import find_mismatch

class Check(unittest.TestCase):
    def test_match(self):
        for text in ('(())[]{{}}{}[]',
                     '{{}}[()]',
                     'foo(bar);'):
            self.assertEqual(find_mismatch(text), 'Success')

    def test_mismatch(self):
        for text, answer in (('()(', 3),
                     ('[', 1),
                     ('}', 1),
                     ('{{{(}}}', 5),
                     ('[[]][]([]', 7),
                     ('[]}](())', 3),
                     ('foo((bar);', 4)):
            self.assertEqual(find_mismatch(text), answer)


if __name__ == '__main__':
    unittest.main()
