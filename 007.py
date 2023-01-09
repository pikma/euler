# https://projecteuler.net/problem=7

import itertools
import math
import typing


def is_prime(i: int, smaller_primes: typing.List[int]):
    sqrt_i = math.sqrt(i)
    for p in smaller_primes:
        if p > sqrt_i:
            break
        if i % p == 0:
            return False
    return True


def generate_primes():
    primes = []
    for i in itertools.count(start=2):
        if is_prime(i, primes):
            primes.append(i)
            yield i


list(itertools.islice(generate_primes(), 10000, 10001))[0]
