import math
from collections import deque

def is_prime(number):
    if number == 2 or number == 3:
        return True
    for div in range(2, math.ceil(math.sqrt(number))+1):
        if number % div == 0:
            return False
    return True

def find_first_n_primes(n):
    primes = []
    number = 2
    while len(primes) < n:
        while not is_prime(number):
            number += 1
        primes.append(number)
        number += 1
    return primes

def split_numbers(numbers, prime):
    a, b = deque(), deque()
    for number in numbers:
        if number % prime == 0:
            b.append(number)
        else:
            a.appendleft(number)
    return list(a), list(b)

def waiter(numbers, q):
    primes = find_first_n_primes(q)
    answers = []
    for i in range(q):
        a, b = split_numbers(numbers, primes[i])
        answers.extend(b)
        numbers = a
    answers.extend(reversed(numbers))
    return answers