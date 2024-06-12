#include "allocator.h"
#include "constructor.h"
#include "debug.h"
#include "def.h"
#include "log.h"
#include <unistd.h>

class A {
public:
  A() {
    LOG_DEBUG("A(a=0)\n");
    m_a = 0;
  }
  A(int a) : m_a(a) { LOG_DEBUG("A(a=%%d)\n", m_a); }
  ~A() { LOG_DEBUG("~A(a=%d)\n", m_a); }

private:
  int m_a;
};

class Alloc1: public y::Constructor<Alloc1> {
private:
  void *alloc_memory(size_t size) { return ::malloc(size); }
  void *realloc_memory(void *ptr, size_t size) { return ::realloc(ptr, size); }
  void free_memory(void *ptr) { return ::free(ptr); }

  friend y::Allocator<Alloc1>;
};

y::RET test1() {
  Alloc1 alloc;
  int COUNT = 500000;
  if (fork()) {
    COST_TIME(
        {
          for (int i = 0; i < COUNT; i++) {
            A *a = g_new<A>(&alloc, i);
            y::g_delete(&alloc, a);
          }
        },
        "CRTP");
  } else {
    COST_TIME(
        {
          for (int i = 0; i < COUNT; i++) {
            A *a = new A(i);
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