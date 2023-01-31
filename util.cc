#include <cmath>
#include <vector>

std::vector<int> Fibonacci(int max_incl) {
  std::vector<int> result;

  int previous = 1;
  int current = 1;
  while (current <= max_incl) {
    result.push_back(current);
    int tmp = previous + current;
    previous = current;
    current = tmp;
  }

  return result;
}

namespace {
bool IsPrime(int n, const std::vector<int>& smaller_primes) {
  double sqrt_n = std::sqrt(n);
  for (int p : smaller_primes) {
    if (p > sqrt_n) {
      break;
    }
    if (n % p == 0) {
      return false;
    }
  }
  return true;
}

}  // namespace

std::vector<int> Primes(int max_incl) {
  std::vector<int> primes;
  for (int i = 2; i <= max_incl; ++i) {
    if (IsPrime(i, primes)) {
      primes.push_back(i);
    }
  }
  return primes;
}
