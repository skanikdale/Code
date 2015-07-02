#include "stdafx.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

class add_x
{
public:
  add_x(int x): x(x) {}
  add_x(int x, int y): x(x), y(y) {}

  double operator()(double y, double z) { return x + y + z;}
  double operator*(double y) { return x* y; }

private:
  double x;
  double y;
};

void testFunctors()
{
  add_x no42(42);

  

  double temp = no42(5.2, 6.3);
  temp = no42*2;

  temp = no42*33;

  std::vector<double> in;
  std::vector<double> out;

  in.push_back(22);
  in.push_back(23);
  in.push_back(233);
  in.push_back(2233);

  out.push_back(22);
  out.push_back(23);
  out.push_back(233);
  out.push_back(2233);

  add_x* pObj = new add_x(23);

  double tet = (*pObj)*33;

  // std::transform(in.begin(), in.end(), out.begin(), add_x(1, 7));

  // std::transform(in.begin(), in.end(), out.begin(), [](double &i){ i+=1;});
}

void testLambada()
{
  // Create a vector object that contains 10 elements.
  std::vector<int> v;

  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }

  // Count the number of even numbers in the vector by 
  // using the for_each function and a lambda.
  int evenCount = 0;

  for_each(v.begin(), v.end(), [&evenCount] (int n) -> int {
  
    if (n % 2 == 0) {
  
      ++evenCount;
      return evenCount;

    } else {
  
    }
  });

  // traditional method
  std::vector<int>::iterator it;

  for(it = v.begin(); it != v.end(); it++)
  {
    if(*it % 2 == 0)
      ++evenCount;
  }

  testFunctors2();
}

class FunctorClass
{
public:
  // The required constructor for this example.
  explicit FunctorClass(int& evenCount)
    : m_evenCount(evenCount) { }

  // The function-call operator prints whether the number is
  // even or odd. If the number is even, this method updates
  // the counter.
  void operator()(int n) const {
    if (n % 2 == 0) {
      ++m_evenCount;
    } else {
    }
  }

private:
  // Default assignment operator to silence warning C4512.
  FunctorClass& operator=(const FunctorClass&);

  int& m_evenCount; // the number of even variables in the vector.
};

void testFunctors2()
{
  int evenCount = 0;
  std::vector<int> vec;
  std::vector<int>::iterator itr;
  
  for(int i = 0; i < 10; i++)
    vec.push_back(i);

  /*FunctorClass obj(evenCount);

  for(itr = vec.begin(); itr != vec.end(); itr++)
      obj(*itr);*/

  for_each(vec.begin(), vec.end(), FunctorClass(evenCount));

  int temp = evenCount;
}