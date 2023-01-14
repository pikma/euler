from typing import Iterator, Tuple
import itertools
import math
import numpy as np
import time


def fibonacci() -> Iterator[int]:
    previous = 0
    current = 1
    while True:
        next = previous + current
        previous = current
        current = next
        yield current


def valid_pythagorean_pairs(max_distance: float) -> Iterator[Tuple[int, int]]:
    ''' Returns each pythagorean pair whose distance is a fibonacci number.

    Dedupes pairs: for example it will yield (3, 4) but won't yield (4, 3).

    max_distance is inclusive.
    '''
    fibonaccis = set(itertools.takewhile(
        lambda _x: _x <= max_distance, fibonacci()))
    # See https://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
    # for why this algorithm generates each pythagorean triple once.
    #
    # This algorithm is way faster than iterating over a and b directly.
    sqrt_max_distance = math.sqrt(max_distance)
    for m in range(1, int(sqrt_max_distance) + 1):
        m_square = m * m
        for n in range(m):
            if math.gcd(m, n) != 1:
                continue
            if m % 2 == 1 and n % 2 == 1:
                continue
            n_square = n * n
            c = m_square + n_square
            a = m_square - n_square
            b = 2 * m * n
            for k in range(1, max_distance // c + 1):
                if k * c in fibonaccis:
                    yield (k * a, k * b)


MODULO = 1000000007


def num_paths(max_i: int) -> np.ndarray:

    max_distance = int(max_i * math.sqrt(2))
    valid_arcs = list(valid_pythagorean_pairs(max_distance))
    valid_arcs += [tuple(reversed(pair)) for pair in valid_arcs]

    # We split the valid arcs into two groups sorted by x or y, so that we can
    # stop early when we iterate through them.
    valid_arcs_by_y = sorted(
        [a for a in valid_arcs if a[0] < a[1]], key=lambda _p: _p[1])
    valid_arcs_by_x = sorted([a for a in valid_arcs if a[0] >= a[1]])

    t = time.time()

    num_paths_array = []
    for i in range(max_i+1):
        num_paths_array.append([0]*(i+1))
        for j in range(i+1):
            if i == 0 and j == 0:
                num_paths_array[i][j] = 1
                continue
            num_paths_for_i_j = 0

            for arc in valid_arcs_by_y:
                smaller_j = j - arc[1]
                if smaller_j < 0:
                    # The valid arcs are sorted by increasing y, therefore the
                    # next arcs are all going to have y too large as well.
                    #  continue
                    break
                smaller_i = i - arc[0]
                if smaller_i < 0:
                    # Cannot take that arc.
                    continue
                if smaller_j > smaller_i:
                    smaller_i, smaller_j = smaller_j, smaller_i
                num_paths_for_i_j += num_paths_array[smaller_i][smaller_j]

            for arc in valid_arcs_by_x:
                smaller_i = i - arc[0]
                if smaller_i < 0:
                    break
                smaller_j = j - arc[1]
                if smaller_j < 0:
                    continue
                if smaller_j > smaller_i:
                    smaller_i, smaller_j = smaller_j, smaller_i
                num_paths_for_i_j += num_paths_array[smaller_i][smaller_j]

            # Valid_arcs has ~100 elements, so num_paths_for_i_j is roughly
            # 100e9, which fits in an int64. That guarantees that we haven't
            # overflowed so far.
            num_paths_array[i][j] = num_paths_for_i_j % MODULO

    print(f'Time: {time.time() - t}s.')
    #  for i in range(len(num_paths_array)):
    #      for j in range(len(num_paths_array[i])):
    #          print(f'{num_paths_array[i][j]: 11}', end='')
    #      print('')

    return num_paths_array


N = 2000


print(f'Result: {num_paths(N)[N][N]}')
