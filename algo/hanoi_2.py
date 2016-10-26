pickzero = lambda x: [0, 1, 28, 2, 29, 14, 24, 3,
                      30, 22, 20, 15, 25, 17, 4, 8,
                      31, 27, 13, 23, 21, 19, 16, 7,
                      26, 12, 18, 6, 11, 5, 10, 9][((x & -x) * 125613361) >> 27]
showpos = lambda x, y: [['A', 'C'], ['B', 'A'], ['C', 'B']][x][y]

count = int(input('Count? '))
if count > 10 or count < 0:
    raise Exception('Input error')

print('Go!')

totalstep = 2 ** count - 1

for step in range(totalstep):
    target = pickzero(step + 1)
    print('Step', step + 1, ':',
          'move', target + 1,
          'from', showpos(step % 3, target % 2),
          'to', showpos(step % 3, 1 - target % 2))

print('Finished.')
print('Total steps :', totalstep)
