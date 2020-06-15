def anagrams(words):
    words = list(set(words))
    d = {}
    for i in range(len(words)):
        s = ''.join(sorted(words[i]))
        # d.setdefault(s, []).append(i)
        if s in d:
            d[s].append(i)
        else:
            d[s] = [i]
    response = []
    for s in d:
        if len(d[s]) > 1:
            response.append([words[i] for i in d[s]])
    return response

if __name__ == "__main__":
    print(anagrams(['le', 'chien', 'marche', 'vers', 'sa', 'niche', 'et', 'trouve', 'une', 'limace', 'de', 'chine', 'nue', 'pleine', 'de', 'malice', 'qui', 'lui', 'fait', 'du', 'charme']))