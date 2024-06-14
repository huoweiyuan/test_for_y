#include "allocator.h"
#include "constructor.h"
#include "debug.h"
#include "def.h"
#include "log.h"
#include <unistd.h>

class A {
public:
  A() {
    LOG_DEBUG("A(nullptr)\n");
    ptr = nullptr;
  }
  A(void *p) : ptr(p) { LOG_DEBUG("A(a=%p)\n", ptr); }
  ~A() { LOG_DEBUG("~A(a=%p)\n", ptr); }

private:
  void *ptr;
};

class Alloc1: public y::Constructor<Alloc1>, public y::Allocator<Alloc1> {
private:
  void *do_alloc(size_t size) { return ::malloc(size); }
  void *do_realloc(void *ptr, size_t size) { return ::realloc(ptr, size); }
  void do_free(void *ptr) { return ::free(ptr); }

  friend y::Allocator<Alloc1>;
  friend y::Constructor<Alloc1>;
};

y::RET test1() {
  Alloc1 alloc;
  int COUNT = 500000;
  if (fork()) {
    COST_TIME(
        {
          for (int i = 0; i < COUNT; i++) {
            A *a = g_new<A>(&alloc, &alloc);
            y::g_delete(&alloc, a);
          }
        },
        "CRTP");
  } else {
    COST_TIME(
        {
          for (int i = 0; i < COUNT; i++) {
            A *a = new A;
            delete a;
          }
        },
        "SYSTEM");
  }
  return Y_SUCCESS;
}

int main() {
  test1();
  return 0;
}