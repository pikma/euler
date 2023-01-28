#pragma once

#include <vector>

// Returns fibonacci number up to "max_incl" (included). The first one is not
// repeated: the sequence returned starts with 1, 2, 3, etc.
std::vector<int> Fibonacci(int max_incl);
