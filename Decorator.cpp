#include "stdafx.h"

//interface Window{
//
//  virtual void draw() = 0;
//};
//
//class SimpleWindow : public Window
//{
//  virtual void draw()
//  {
//    printf("Simple Window"); 
//  }
//
//public:
//  SimpleWindow* operator +(SimpleWindow* pSecondObj)
//  {
//    SimpleWindow* pObj = new SimpleWindow();
//
//    /* Combine attributes of 2 objects on a new object. */
//    // pObj = this + pSecondObj;
//
//    return pObj;
//  }
//
////public:
////  double operator + (double y)
////  {
////    return y * y;
////  }
//};
//
//class TitleWindow : public SimpleWindow
//{
//  virtual void draw()
//  {
//    printf("Title Window"); 
//  }
//};
//
//class SideWindow : public SimpleWindow
//{
//  virtual void draw()
//  {
//    printf("side window"); 
//  }
//};
//
//void test_decorator()
//{
//  /*Window* pWin = new SimpleWindow() + new TitleWindow() + new SideWindow();
//
//  pWin->draw();*/
//
//  SimpleWindow* obj = new SimpleWindow();
//  SideWindow* obj1 = new SideWindow();
//  TitleWindow* obj2 = new TitleWindow();
//
//  //(*obj)+(obj1);
//  //(*obj1)+(obj2);
//
//  //SimpleWindow* obj3 = obj1 + obj2;
//}

interface I{

public:
  virtual ~I(){}
  virtual void do_it() = 0;
};

class A : public I
{
public:
  void do_it()
  {
    printf("A");
  }
};

class D: public I
{
public:
  D(I* pIns)
  {
    m_pInstance = pIns;
  }

  void do_it()
  {
    m_pInstance->do_it();
  }

  ~D()
  {
    delete m_pInstance;
  }

private:
  I* m_pInstance;
};

class X : public D
{
public:
  X(I* pIns):D(pIns)
  {

  }

  void do_it()
  {
    D::do_it();
    printf("X");
  }
};

class Y : public D
{
public:
  Y(I* pIns):D(pIns)
  {

  }

  void do_it()
  {
    D::do_it();
    printf("Y");
  }
};

void test_decorator()
{
  I* one = new X(new A);
  I* two = new Y(new X(new A));
}