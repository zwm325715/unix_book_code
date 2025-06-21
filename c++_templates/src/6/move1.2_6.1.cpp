#include <utility>
#include <iostream>
using namespace std;
class X {};

void g (X&) {
  std::cout << "g() for variable\n";
}
void g (X const&) {
  std::cout << "g() for constant\n";
}
void g (X&& /*右值引用*/) {
  std::cout << "g() for movable object\n";
}

//C++11完美转发
template<typename T>
void f(T&& val) {
  g(std::forward<T>(val));//完美转发val参数给g()
}

int main() {
  X v;              // create variable
  X const c;        // create constant
  // f() for nonconstant object calls f(X&)  =>  calls g(X&)
  f(v);  //非常量对象
  // f() for constant object calls f(X const&) =>  calls g(X const&)
  f(c);  //常量对象(const也会保留)
  // f() for temporary calls f(X&&)  =>  calls g(X&&)
  f(X()); //临时对象
  // f() for movable variable calls f(X&&)  => calls g(X&&)
  f(std::move(v)); //可移动变量
}