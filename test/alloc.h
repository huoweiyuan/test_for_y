#ifndef TEST_ALLOC_H
#define TEST_ALLOC_H
#include "y/includes/alloc.h"
#include <gtest/gtest.h>
#include <iostream>

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
  y::SimpleSysAlloc alloc;
  AllocTest *test = y::g_new<AllocTest>(&alloc);
  y::g_delete(test);
}

TEST(ALLOC, new2)
{
  y::SimpleSysAlloc alloc;
  AllocTest *test = y::g_new<AllocTest, 3>(&alloc, 1);
  y::g_delete(test);
}

TEST(ALLOC, new3)
{
  y::SimpleSysAlloc *alloc = new y::SimpleSysAlloc();
  AllocTest *test = y::g_new<AllocTest, 3>(alloc, 1);
  y::g_delete(test);
  delete alloc;
}

#endif