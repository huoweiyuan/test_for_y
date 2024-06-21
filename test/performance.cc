#include "stlallocator.h"
#include <functional>
#include <string>
#include <unistd.h>
#include <unordered_set>

template<typename T>
class SimpleStlAlloc2: public y::StlAllocator<T, SimpleStlAlloc2> {
  ALLOCATOR_PATCH(SimpleStlAlloc2)
private:
  void *do_alloc(size_t size) { return ::malloc(size); }
  void do_free(void *ptr) { return ::free(ptr); }

  friend y::StlAllocator<T, SimpleStlAlloc2>;

};

using String =
    std::basic_string<char, std::char_traits<char>, SimpleStlAlloc2<char>>;

namespace std {
template <> struct hash<String> {
  using argument_type = String;
  using result_type = std::size_t;
  result_type operator()(const argument_type &s) const {
    result_type hash_value = 0;
    for (char c : s) {
      hash_value = 31 * hash_value + c;
    }
    return hash_value;
  }
};
} // namespace std

template<typename T>
using Unordered_set = std::unordered_set<T, std::hash<T>, std::equal_to<T>, SimpleStlAlloc2<T>>;

void test_stl() {
  Unordered_set<String> set1;
  set1.insert("asd");
}

int main() {
  test_stl();
  return 0;
}