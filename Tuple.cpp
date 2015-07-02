#include "stdafx.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <string>

using namespace std;

typedef tuple<int, double, string> ids;

void test_tuple()
{
  // Using the constructor to declare and initialize a tuple
  ids p1(10, 10.1, "One");

  ids p2;

  p2 = make_tuple(20, 20.2, "two");

  ids p3;

  p3 = p2;

}