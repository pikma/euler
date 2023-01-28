#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <utility>
#include <vector>

#include "util.h"

struct Arc {
  int x;
  int y;
};

std::vector<Arc> ValidArcs(int width, int height) {
  double max_distance = std::sqrt(width * width + height * height);
  const std::vector<int> fibonacci_numbers_vec =
      Fibonacci(static_cast<int>(max_distance));
  const std::unordered_set<int> fibonacci_numbers(
      fibonacci_numbers_vec.cbegin(), fibonacci_numbers_vec.cend());

  std::vector<Arc> result;
  for (int m = 1; m <= max_distance; ++m) {
    int m2 = m * m;
    for (int n = 0; n < m; ++n) {
      if (m % 2 == 1 && n % 2 == 1) {
        continue;
      }
      if (std::gcd(m, n) != 1) {
        continue;
      }

      int n2 = n * n;
      int c = m2 + n2;
      int a = m2 - n2;
      int b = 2 * m * n;

      for (int k = 1; k <= max_distance / c; ++k) {
        if (fibonacci_numbers.find(k * c) != fibonacci_numbers.cend()) {
          if (k * a <= width && k * b <= height) {
            result.push_back(Arc{.x = k * a, .y = k * b});
          }
          if (k * b <= width && k * a <= height) {
            result.push_back(Arc{.x = k * b, .y = k * a});
          }
        }
      }
    }
  }
  return result;
}

int NumPaths(int width, int height) {
  // NumPaths(i, j) == NumPaths(j, i), so we only compute and store the
  // ones where i <= j. Therefore we set width <= height.
  width = std::min(width, height);
  height = std::max(width, height);

  constexpr int kModulo = 1000000007;
  std::vector<Arc> valid_arcs = ValidArcs(width, height);

  std::vector<std::vector<int>> num_paths;
  num_paths.reserve(width + 1);
  for (int i = 0; i <= width; ++i) {
    num_paths.push_back(std::vector<int>(height + 1));
    for (int j = 0; j <= height; ++j) {
      if (i == 0 && j == 0) {
        num_paths[i][j] = 1;
        continue;
      }

      // Valid_arcs has ~100 elements, so num_paths_for_i_j is roughly 100e9,
      // which fits in an int64. This way, we can do one modulo at the end of
      // the sum rather than for each term in the sum.
      uint64_t num_paths_i_j = 0;
      for (const Arc &arc : valid_arcs) {
        // We iterate over the possible last arcs of the path.
        int smaller_i = i - arc.x;
        int smaller_j = j - arc.y;
        if (smaller_i < 0 || smaller_j < 0) {
          // This arc is too large.
          continue;
        }

        if (smaller_i > smaller_j) {
          // We only stores the ones where i <= j.
          int tmp = smaller_i;
          smaller_i = smaller_j;
          smaller_j = tmp;
        }
        num_paths_i_j += num_paths[smaller_i][smaller_j];
      }
      num_paths[i][j] = static_cast<int>(num_paths_i_j % kModulo);
    }
  }

  return num_paths[width][height];
}

int main() {
  std::cout << "Fibonacci(10000): ";
  for (int i : Fibonacci(10000)) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  auto valid_arcs = ValidArcs(100, 100);
  std::cout << "ValidArcs(100, 100): ";
  for (const Arc &arc : valid_arcs) {
    std::cout << "(" << arc.x << ", " << arc.y << ") ";
  }
  std::cout << std::endl;

  std::cout << "NumPaths(3, 4) = " << NumPaths(3, 4) << std::endl;
  std::cout << "NumPaths(10, 10) = " << NumPaths(10, 10) << std::endl;
  std::cout << "NumPaths(10000, 10000) = " << NumPaths(10000, 10000)
            << std::endl;
  return EXIT_SUCCESS;
}
