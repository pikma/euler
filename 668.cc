// See https://projecteuler.net/problem=668.
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "absl/log/absl_check.h"
#include "util.h"

int64_t NumSquareRootSmoothNumbers(int64_t max_incl) {
  // Any square root smooth number no larger than max_incl cannot have any prime
  // factor larger than sqrt(max_incl).
  int sqrt_max_incl = static_cast<int>(std::sqrt(max_incl));
  std::vector<int> primes = Primes(sqrt_max_incl);
  // std::cout << "Primes: " << PrintCollection(primes) << std::endl;

  std::vector<int> exponents(primes.size(), 0);
  if (max_incl < 8) {
    return 0;
  }
  ABSL_CHECK_GE(exponents.size(), 1ull);
  // We start at the first valid square root smooth number, which is 2³ = 8.
  exponents[0] = 3;
  int64_t current_number = 8;
  unsigned int max_exponent = 0;

  // According to the problem definition, should be counted. We also count 8.
  int64_t num_root_smooth_numbers = 2;
  while (true) {
    bool found_next_number = false;
    for (unsigned int i = 0; i < exponents.size(); ++i) {
      int64_t new_number = current_number * primes[i];
      if (new_number <= max_incl) {
        // We can increment this exponent.
        ++exponents[i];
        if (i > max_exponent) {
          max_exponent = i;
        }
        current_number = new_number;
        // Resets the exponents < i.
        for (unsigned int j = 0; j < i; ++j) {
          exponents[j] = 0;
        }
        found_next_number = true;
        break;
      } else {
        const bool exponent_was_zero = exponents[i] == 0;
        // We can't increment this exponent. We set it to zero and move on to
        // the higher primes.
        while (exponents[i] > 0) {
          current_number /= primes[i];
          --exponents[i];
        }

        if (exponent_was_zero) {
          // Setting this prime's power to 1 made the total number go over the
          // limit. We know that trying to set to 1 any larger prime's exponent
          // will do the same. We can skip them.
          while (i + 1 < exponents.size() && exponents[i + 1] == 0) {
            ++i;
          }
        }
      }
    }
    if (!found_next_number) {
      // We've cycled through all the possible numbers.
      break;
    }

    // We need to convert to int64s since p*p could overflow.
    if (int64_t p = primes[max_exponent]; p * p < current_number) {
      if (num_root_smooth_numbers % 10'000'000 == 0) {
        std::cout << current_number << ": ";
        for (unsigned int i = 0; i <= max_exponent; ++i) {
          if (exponents[i] > 1) {
            std::cout << primes[i] << "^" << exponents[i] << " x ";
          } else if (exponents[i] == 1) {
            std::cout << primes[i] << " x ";
          }
        }
        std::cout << std::endl;
        // << PrintCollection(exponents) << std::endl;
      }
      ++num_root_smooth_numbers;
    }
  }

  return num_root_smooth_numbers;
}

int main() {
  std::cout << NumSquareRootSmoothNumbers(10'000'000'000ll) << std::endl;
  // std::cout << NumSquareRootSmoothNumbers(100ll) << std::endl;
  return EXIT_SUCCESS;
}
