#ifndef TEST_ALLOC_H
#define TEST_ALLOC_H
#include "allocator.h"
#include "y/includes/constructor.h"
#include <gtest/gtest.h>
#include <iostream>

#include "y/includes/debug.h"

class SimpleSysAlloc : public y::Constructor<SimpleSysAlloc>, public y::Allocator<SimpleSysAlloc> {
  friend y::Constructor<SimpleSysAlloc>;
  friend y::Allocator<SimpleSysAlloc>;

private:
  void *do_alloc(size_t size) { return ::malloc(size); }
  void *do_realloc(void *ptr, size_t size) { return ::realloc(ptr, size); }
  void do_free(void *ptr) { return ::free(ptr); }
};

class AllocTest
{
  int m_a = 0;
  public:
  AllocTest()
  {
    std::cout << "Alloc AllocTest" << std::endl;
  }

  AllocTest(int a)
  {
    m_a = a;
    std::cout << "Alloc AllocTest(int)" << std::endl;
  }

  ~AllocTest()
  {
    if (m_a != 0) {
      std::cout << "Free AllocTest(int) a = " << m_a << std::endl;
    } else {
      std::cout << "Free AllocTest" << std::endl;
    }
  }
};

TEST(ALLOC, new1)
{
  SimpleSysAlloc alloc;
  AllocTest *test = y::g_new<AllocTest>(&alloc);
  y::g_delete(&alloc, test);
}

TEST(ALLOC, new2)
{
  SimpleSysAlloc alloc;
  AllocTest *test = y::g_new<AllocTest, 3>(&alloc, 1);
  y::g_delete(&alloc, test);
}

TEST(ALLOC, new3)
{
  SimpleSysAlloc *alloc = new SimpleSysAlloc();
  AllocTest *test = y::g_new<AllocTest, 3>(alloc, 1);
  y::g_delete(alloc, test);
  delete alloc;
}

TEST(ALLOC, alloc1) {
  SimpleSysAlloc *alloc = new SimpleSysAlloc();
  char *test = static_cast<char *>(y::g_alloc(alloc, 128));
  y::g_free(alloc, test);
  delete alloc;
}

#endif