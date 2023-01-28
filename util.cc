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
