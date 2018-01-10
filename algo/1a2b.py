import random
import itertools

tot = int(input('size? '))

pool = list(itertools.permutations(range(10), tot))
random.shuffle(pool)

guess = []

for x in pool:
    for (xx, aa, bb) in guess:
        a = 0
        b = 0
        for i in range(tot):
            a += int(x[i] == xx[i])
            b += int(x[i] in xx and x[i] != xx[i])
        if a != aa or b != bb:
            break
    else:
        print(x)
        line = input().split()
        if len(line) == 0:
            exit()
        elif len(line) == 1:
            guess.append((x, int(line[0]), tot - int(line[0])))
        elif len(line) == 2:
            guess.append((x, int(line[0]), int(line[1])))
