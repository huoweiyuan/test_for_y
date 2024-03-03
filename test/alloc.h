#include "y/include/alloc.h"
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
  y::Allocator alloctor;
  alloctor.set_as_default_allocator();
  AllocTest *test = new (&alloctor) AllocTest();
  delete test;
}

TEST(ALLOC, new2)
{
  y::Allocator alloctor;
  alloctor.set_as_default_allocator();
  AllocTest *test = new AllocTest[3]{{1},{2}};
  delete[] test;
}

TEST(ALLOC, new3)
{
  y::Allocator *alloctor = new y::Allocator();
  alloctor->set_as_default_allocator();
  AllocTest *test = new (alloctor) AllocTest[3]{{1},{2}};
  delete[] test;
}