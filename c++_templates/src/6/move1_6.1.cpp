#include <utility>
#include <iostream>

class X {
  //...
};

void g (X&) {
  std::cout << "g() for variable\n";
}
void g (X const&) {
  std::cout << "g() for constant\n";
}
void g (X&& /*右值引用*/) {
  std::cout << "g() for movable object\n";
}

// let f() forward argument val to g(): 让f()转发实参val给g()
void f (X& val) {
  // val is non-const lvalue => calls g(X&)  非常量左值=>调用g(X&)
  g(val);
}
void f (X const& val) {
  // val is const lvalue => calls g(X const &)  常量左值
  g(val);
}
void f (X&& val) {
  // val is non-const lvalue => needs std::move() to call g(X&&)
  // 非常量左值 => 需要使用std::move()来调用g(X&&)
  g(std::move(val)/*转换为右值引用*/);
}

int main() {
  X v;              // create variable
  X const c;        // create constant
  // f() for nonconstant object calls f(X&)  =>  calls g(X&)
  f(v);  //非常量对象

  // f() for constant object calls f(X const&) =>  calls g(X const&)
  f(c);   //常量对象xzz

  // f() for temporary calls f(X&&)  =>  calls g(X&&)
  f(X()); //临时对象

  // f() for movable variable calls f(X&&)  => calls g(X&&)
  f(std::move(v)); //可移动变量
}
