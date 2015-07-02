#include "stdafx.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#define TRACE printf

class RefCount
{

public:
  RefCount() { crefs = 0; }

  ~RefCount() 
  {
    TRACE("Goodbye (%d) \n", crefs);
  }

  void upCount()
  {
    crefs++;

    TRACE("Up to (%d) \n", crefs);
  }

  void downCount()
  {

    if(--crefs == 0)
      delete this;
    else
      TRACE("Down to (%d) \n", crefs);
  }

private:
  int crefs;
};

class Sample:public RefCount
{
public:
  void doSomething()
  {
    TRACE("did something \n");
  }
};

template <class T> class Ptr
{
public:

  // Constructor.... If someone is instantiating obj then incre ref count
  Ptr(T* obj):m_ptr(obj)
  {
      m_ptr->upCount();
  }

  ~Ptr()
  {
    m_ptr->downCount();
  }

  operator T* ()
  {
    return m_ptr;
  }

  T& operator*()
  {
    return *m_ptr;
  }

  T* operator->()
  {
    return m_ptr;
  }

  Ptr& operator = (Ptr<T> &p_) {
    return operator=((T *) p_);
  }

  Ptr& operator = (T* p_) {
    p_->upCount();
    m_ptr->downCount();
    m_ptr = p_;
    return *this;
  }

  Ptr(const Ptr<T> &p_) {
    m_ptr = p_.m_ptr;
    m_ptr->upCount();
  };

private:
  T* m_ptr;
};

void testGarbageCollector()
{
  Ptr<Sample> obj1 = new Sample();
  Ptr<Sample> obj2 = new Sample();

  obj1 = obj2;
  // #1 will have 0 crefs, so it is destroyed;
  // #2 will have 2 crefs.

  obj1->doSomething();

  return;
  // As p2 and p go out of scope, their destructor call
  // down count. The cref variable of #2 goes to 0, so #2 is
  // destroyed
}