t9 = "22233344455566677778889999"
#     abcdefghijklmnopqrstuvwxyz   mapping on the phone


def letter_to_digit(x):
    """:returns: the digit correspondence for letter x"""
    assert 'a' <= x <= 'z'
    return t9[ord(x) - ord('a')]


def code_word(word):
    """:returns: the digit correspondence for given word"""
    return ''.join(map(letter_to_digit, word))


def predictive_text(dic):
    """Predictive text for mobile phones

    :param dic: associates weights to words from [a-z]*
    :returns: a dictionary associating to words from [2-9]*
             a corresponding word from the dictionary with highest weight
    :complexity: linear in total word length
    """
    # total_weight[p] = total weight of words having prefix p
    total_weight = {}
    for word, weight in dic:
        prefix = ""
        for x in word:
            prefix += x
            if prefix in total_weight:
                total_weight[prefix] += weight
            else:
                total_weight[prefix] = weight
    # prop[s] = prefix to display for s
    prop = {}
    for prefix in total_weight:
        code = code_word(prefix)
        if (code not in prop
                or total_weight[prop[code]] < total_weight[prefix]):
            prop[code] = prefix
    return prop


def propose(prop, seq):
    """wrapper to access a dictionary even for non-present keys"""
    if seq in prop:
        return prop[seq]
    return None


import unittest

class TestTryalgo(unittest.TestCase):
    def test_predictive_text(self):
        dico = [("another", 5), ("contest", 6), ("follow", 3),
                ("give", 13), ("integer", 6), ("new", 14), ("program", 4)]
        prop = predictive_text(dico)
        A = ""
        for seq in ["7764726", "639", "468", "2668437", "7777"]:
            for i in range(len(seq)):
                A += str(propose(prop, seq[:i + 1])) + " "
        self.assertEqual(
            A, "p pr pro prog progr progra program n ne new g "
            "in int c co con cont anoth anothe another p pr None None ")

if __name__ == '__main__':
    unittest.main()
