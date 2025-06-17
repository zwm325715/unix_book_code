#include "arrays_5.4.hpp"

//在使用数组时，各种情况都可能发生
template<typename T1, typename T2, typename T3>
void foo(int a1[7], int a2[],// pointers by language rules 根据语言规则划分指针类型
         int (&a3)[42], // reference to array of known bound 已知边界数组的引用
         int (&x0)[],   // reference to array of unknown bound 未知边界数组的引用
         T1 x1, // passing by value decays 传值会产生退化
         T2& x2, T3&& x3)// passing by reference 传引用
{
  //根据语言规则声明为数组(定长或变长)的调用参数(形参)实际上是指针类型
  MyClass<decltype(a1)>::print();     // uses MyClass<T*>
  MyClass<decltype(a2)>::print();     // uses MyClass<T*>
  //引用不会退化
  MyClass<decltype(a3)>::print();     // uses MyClass<T(&)[SZ]>
  std::cout << "-----------------------" << std::endl;
  MyClass<decltype(x0)>::print();     // uses MyClass<T(&)[]>
  //如果x1是数组时，就会退化指针
  MyClass<decltype(x1)>::print();     // uses MyClass<T*>
  //不完整类型是按引用传递时,会变成T(&)[]类型
  MyClass<decltype(x2)>::print();     // uses MyClass<T(&)[]>
  MyClass<decltype(x3)>::print();     // uses MyClass<T(&)[]>
}

int main() {
  int a[42];
  MyClass<decltype(a)>::print(); // uses MyClass<T[SZ]>

  //这是一个不完整(未指定数组大小,因此编译器不知道数组的实际长度)的数组类型声明:
  //  表示x是一个在别处定义的数组(可能在其他文件或同一文件的后面定义)
  extern int x[];  // forward declare array 前置声明数组
  //未知边界数组的模版可以用于不完整类型
  MyClass<decltype(x)>::print(); // uses MyClass<T[]>

  foo(a, a, a, x, x, x, x);
}

int x[] = {0, 8, 15};  // define forward-declared array 定义前置声明数组
