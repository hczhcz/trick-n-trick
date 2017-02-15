n = 9

for i in range(n * (n + 1) // 2):
    line = int(((8 * i + 1) ** 0.5 - 1)) // 2

    x = i - line * (line + 1) // 2 + 1
    y = line + 1

    print(str(x) + '*' + str(y) + '=' + str(x * y), end=chr(10 + 22 * int(x != y)))
