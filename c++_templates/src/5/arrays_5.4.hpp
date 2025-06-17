#include <iostream>

template<typename T>
// primary template 主模版
struct MyClass;

template<typename T, std::size_t SZ>
// partial specialization for arrays of known bounds 已知边界数组的偏特化
struct MyClass<T[SZ/*边界*/]>   {
  static void print() {
    std::cout << "print() for T[" << SZ << "]\n";
  }
};

template<typename T, std::size_t SZ>
// partial spec. for references to arrays of known bounds 已知边界数组引用的偏特化
struct MyClass<T(&/*引用*/)[SZ/*边界*/]> {
  static void print() {
    std::cout << "print() for T(&)[" << SZ << "]\n";
  }
};

template<typename T>
// partial specialization for arrays of unknown bounds 未知边界数组的偏特化
struct MyClass<T[/*未知边界*/]> {
  static void print() {
    std::cout << "print() for T[]\n";
  }
};

template<typename T>
// partial spec. for references to arrays of unknown bounds 未知边界数组引用的偏特化
struct MyClass<T(&/*引用*/)[/*未知边界*/]> {
  static void print() { std::cout << "print() for T(&)[]\n"; }
};

template<typename T>
// partial specialization for pointers 指针偏特化
struct MyClass<T*/*指针*/> {
  static void print() {
    std::cout << "print() for T*\n";
  }
};
