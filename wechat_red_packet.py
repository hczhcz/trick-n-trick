from random import random

def generate(users, money):
    users = int(users)
    money = int(100 * money)

    if users < 1 or money < users:
        raise "Error!"

    while users > 1:
        amount = int(1 + 2 * (money / users - 1) * random())

        users -= 1
        money -= amount
        yield 0.01 * amount

    yield 0.01 * money

print [amount for amount in generate(5, 1)]
