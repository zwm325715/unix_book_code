#include "max1_1.1.1.hpp"
#include <iostream>
#include <string>

//注意全局命名空间的使用
int main() {
  //1.int类型
  int i = 42;
  std::cout << "max(7,i):   " << ::max(7,i) << '\n';
  
  //2.double类型
  double f1 = 3.4;
  double f2 = -6.7;
  std::cout << "max(f1,f2): " << ::max(f1,f2) << '\n';

  //3.string类型
  std::string s1 = "mathematics";
  std::string s2 = "math";
  std::cout << "max(s1,s2): " << ::max(s1,s2) << '\n';

  //4.默认实参的类型推导
  f(1);
  f();
}
