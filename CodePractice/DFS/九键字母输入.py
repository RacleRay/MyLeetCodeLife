"""
Given a digit string excluded 0 and 1, return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below.
"""

KEYBOARD = {
    '2': 'abc',
    '3': 'def',
    '4': 'ghi',
    '5': 'jkl',
    '6': 'mno',
    '7': 'pqrs',
    '8': 'tuv',
    '9': 'wxyz'
}

def letterCombinations(digits):
    if not digits: return []

    combinations = []
    dfs(digits, 0, [], combinations)
    return combinations

def dfs(digits, index, combination, combinations):
    if index == len(digits):
        combinations.append(''.join(combination))
        return

    for letter in KEYBOARD[digits[index]]:
        combination.append(letter)
        dfs(digits, index + 1, combination, combinations)
        combination.pop()