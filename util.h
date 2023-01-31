#pragma once

#include <ostream>
#include <string>
#include <vector>

// Returns fibonacci number up to "max_incl" (included). The first one is not
// repeated: the sequence returned starts with 1, 2, 3, etc.
std::vector<int> Fibonacci(int max_incl);

// Return prime numbers up to "max_incl" (included).
std::vector<int> Primes(int max_incl);

// A helper class to print collections.
//
// Usage: std::cout << PrintCollection(my_collection).
//
// Works with vectors, sets, or anything that can be iterated over and whose
// elements can be printed.
template <typename Collection>
class PrintCollection {
 public:
  PrintCollection(const Collection& collection)
      : collection_(collection), separator_(", ") {}

  PrintCollection(const Collection& collection, std::string separator)
      : collection_(collection), separator_(separator) {}

 private:
  template <typename C>
  friend std::ostream& operator<<(std::ostream& os,
                                  const PrintCollection<C>& obj);

  const Collection& collection_;
  const std::string separator_;
};

template <typename Collection>
std::ostream& operator<<(std::ostream& os,
                         const PrintCollection<Collection>& obj) {
  bool is_first = true;
  for (const auto& element : obj.collection_) {
    if (is_first) {
      os << element;
    } else {
      os << obj.separator_ << element;
    }
    is_first = false;
  }
  return os;
}
