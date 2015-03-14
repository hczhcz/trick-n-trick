pickzero = lambda x: [0, 1, 28, 2, 29, 14, 24, 3,
                      30, 22, 20, 15, 25, 17, 4, 8,
                      31, 27, 13, 23, 21, 19, 16, 7,
                      26, 12, 18, 6, 11, 5, 10, 9][((x & -x) * 125613361) >> 27]
trans = lambda x: [1, 2, 0, 4, 5, 3][x]
showpos = lambda x: ['A', 'B', 'C', 'A', 'C', 'B'][x]

count = int(input('Count? '))
if count > 10 or count < 0:
    raise Exception('Input error')

print('Go!')

totalstep = 2 ** count - 1

state = [((member & 1) * 3) for member in range(count, 0, -1)]

for step in range(1, totalstep + 1):
    target = pickzero(step)
    oldstate = state[target]
    newstate = trans(oldstate)
    state[target] = newstate
    print('Step', step, ':',
          'move', target + 1,
          'from', showpos(oldstate),
          'to', showpos(newstate))

print('Finished.')
print('Total steps :', totalstep)
