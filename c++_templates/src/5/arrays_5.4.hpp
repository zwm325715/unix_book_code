#include <iostream>

template<typename T>
// primary template 主模版
struct MyClass;

template<typename T, std::size_t SZ>
// partial specialization for arrays of known bounds 已知边界数组的偏特化
struct MyClass<T[SZ]>   {
  static void print() { std::cout << "print() for T[" << SZ << "]\n"; }
};

template<typename T, std::size_t SZ>
// partial spec. for references to arrays of known bounds
struct MyClass<T(&)[SZ]> {
  static void print() { std::cout << "print() for T(&)[" << SZ << "]\n"; }
};

template<typename T>
struct MyClass<T[]>         // partial specialization for arrays of unknown bounds
{
  static void print() { std::cout << "print() for T[]\n"; }
};

template<typename T>
struct MyClass<T(&)[]>      // partial spec. for references to arrays of unknown bounds
{
  static void print() { std::cout << "print() for T(&)[]\n"; }
};

template<typename T>
struct MyClass<T*>          // partial specialization for pointers
{
  static void print() { std::cout << "print() for T*\n"; }
};
