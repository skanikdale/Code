#include "stdafx.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>



template<class /* OR typename*/ T> T add(T a, T b)
{
  return a + b;
}

template <class T> class A
{
public:
    A(T t):m_t(t) {}
    void function(T t);

private:
  T m_t;
};

template < class T> class B
{
public:
  B(T* p_t):m_t(p_t) {}

private:
  T* m_t;
};


// Templates can also be parameterized by a value parameter
template<int i> class D
{
public:
  D() { memset(array, 0, i* sizeof(int)); }

private:
  int array[i];
};

// Template with parameter T and non-type template parameter i

template< class T, int i> class TestClass
{

public:
  char Buffer[i];
  T testFunction(T* p_t);
};

template< class T, int i> 
T TestClass<T, i>::testFunction(T* p_t)
{
  return *(p_t++);
}

// Use array in template
template<class T> double getAverage(T tArrary[], int i)
{
  T tSum = T();  // Initializing to 0;

  for(int j = 0; j < i; j++)
    tSum += tArrary[j];

  return (double) tSum / i;
}


void testTemplates()
{
  // 2 types of templates
      // 1. Function template
      // 2. Class template

  // 1. Function template
  double dOut = add(23.25, 56.55);
  int    nOut = add(433, 343);

  // 2. Class template
  A<int> a(12);
  A<double> d(44.44);

  int temp = 33;

  B<int> c(&temp);
  A<int*> m(&temp);

  D<22> obj;
  
  TestClass<double, 4> obj5;

  int inArrary[4] = { 3, 55, 65, 66 };
  double dArray[5] = { 44, 55, 55, 33, 44};

  double avg = getAverage(inArrary, 4);
  avg = getAverage(dArray, 5);
}