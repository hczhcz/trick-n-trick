import re


def test(word, target):
    wcs = ''.join(
        (
            '='
            if wc == tc
            else wc
        )
        for wc, tc in zip(word, target)
    )
    tcs = ''.join(
        (
            '='
            if wc == tc
            else tc
        )
        for wc, tc in zip(word, target)
    )

    return ''.join(
        str((wc == '=') + (wcs[:i + 1].count(wc) <= tcs.count(wc)))
        for i, wc in enumerate(wcs)
    )


def test_count(word, targets):
    counts = {}

    for target in targets:
        res = test(word, target)
        counts[res] = counts.get(res, 0) + 1

    return counts


size = 5
hard = False
known = [('aloes', '00000')]

words = [
    line[:-1]
    for line in open('/usr/share/dict/words', 'r')
    if len(line) == size + 1 and re.match(r'^[a-z]+$', line[:-1])
]

candidates = [
    target
    for target in words
    if all(
        test(word, target) == res
        for word, res in known
    )
]

if len(candidates) <= 20:
    print('candidates', candidates)

if len(candidates) >= 3:
    print('guess', min(
        (max(test_count(word, candidates).values()), word)
        for word in (
            candidates
            if hard
            else words
        )
    ))
