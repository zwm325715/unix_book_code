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

//初步我们心中的那个模版函数(有问题)
template<typename T>
void f(T val) {
  g(val);
}

int main() {
  X v;              // create variable
  X const c;        // create constant
  // f() for nonconstant object calls f(X&)  =>  calls g(X&)
  f(v);  //非常量对象

  // f() for constant object calls f(X const&) =>  calls g(X const&)
  f(c);  //常量对象(底层const在模版推导过程中被忽略掉了)

  // f() for temporary calls f(X&&)  =>  calls g(X&&)
  f(X()); //临时对象

  // f() for movable variable calls f(X&&)  => calls g(X&&)
  f(std::move(v)); //可移动变量

  //cout<<"-----不转发,直接调用是没问题的-------"<<endl;
  // g(v);g(c);g(X());g(std::move(v));
}