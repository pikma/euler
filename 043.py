#  https://projecteuler.net/problem=43

import itertools
import typing


def number_from_digits_tuple(digits_tuple: typing.Tuple[int]):
    return sum((d * (10**i) for i, d in enumerate(reversed(digits_tuple))))


PRIMES = [2, 3, 5, 7, 11, 13, 17]


def is_pandigital(digits_tuple: typing.Tuple[int]) -> bool:
    for starting_digit in range(7):
        subnumber = number_from_digits_tuple(
            digits_tuple[starting_digit+1:starting_digit+4])
        if subnumber % PRIMES[starting_digit] != 0:
            return False
    return True


def pandigital_numbers() -> typing.Iterable[int]:
    digits = list(range(10))
    for digits_tuple in itertools.permutations(digits):
        if is_pandigital(digits_tuple):
            yield number_from_digits_tuple(digits_tuple)


sum(pandigital_numbers())
