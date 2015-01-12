# http://www.zhihu.com/question/24572110
# for fun

data = [
    ('a', 1),
    ('a', 1),
    ('a', 1),
    ('a', 2),
    ('a', 3),
    ('a', 2),
    ('a', 3),
    ('a', 4),
    ('b', 6),
    ('b', 7),
    ('b', 7),
    ('b', 7),
    ('b', 7),
    ('b', 8)
]

# accept_mode = {
#     (-2, 1),
#     (-1, -1),
#     (-1, 2),
#     (0, 0),
#     (1, 1),
#     (1, -2),
#     (2, -1)
# }

accept_mode = {
    (0, 0),
    (1, 1)
}

accept_set = []

for a in range(14):
    for b in range(14):
        if a == b:
            continue
        for c in range(14):
            if a == c or b == c:
                continue
            if data[a][0] == data[b][0] == data[c][0]:
                if (
                    data[a][1] - data[b][1],
                    data[b][1] - data[c][1]
                ) in accept_mode:
                    accept_set.append({a, b, c})

for m in accept_set:
    for n in accept_set:
        if (m & n) != set():
            continue
        for p in accept_set:
            if (m & p) != set() or (n & p) != set():
                continue
            for q in accept_set:
                if (m & q) != set() or (n & q) != set() or (p & q) != set():
                    continue
                rest = set(range(14)) - m - n - p - q
                lr = list(rest)
                if data[lr[0]] == data[lr[1]]:
                    lm = list(m)
                    ln = list(n)
                    lp = list(p)
                    lq = list(q)
                    print [data[lm[0]], data[lm[1]], data[lm[2]]]
                    print [data[ln[0]], data[ln[1]], data[ln[2]]]
                    print [data[lp[0]], data[lp[1]], data[lp[2]]]
                    print [data[lq[0]], data[lq[1]], data[lq[2]]]
                    print [data[lr[0]], data[lr[1]]]
                    exit()
