#include "stdafx.h"
#include <iostream>
#include <memory>

class second;


class first
{

public:
  // Constructor
  first( ) : m_sptrB() { };
  std::weak_ptr<second> m_sptrB;
};

class second
{
public:
  second() : m_sptrA() {};
  std::weak_ptr<first> m_sptrA;

  void useWeakPtr();
};

void second::useWeakPtr()
{
  std::shared_ptr<first> temp = m_sptrA.lock();
}


void testSmartPtrs()
{
  std::shared_ptr<first> a(new first);
  std::shared_ptr<second> b(new second);

  a->m_sptrB = b;
  b->m_sptrA = a;

  b->useWeakPtr();

  // cout<< m_sptrB.lock( )->m_b<<endl;
}







