#include <iostream>
#include <string>
#include "stackauto_3.4.hpp"

int main() {
  //20u 推导出Stack内的Maxsize类型为unsigned int类型  
  Stack<int,20u>        int20Stack;     
  //40 推导出Stack内的Maxsize类型为int类型  
  Stack<std::string,40> stringStack;    

  // manipulate stack of up to 20 ints
  int20Stack.push(7);
  std::cout << int20Stack.top() << '\n';
  //返回类型为:unsigned int
  auto size1 = int20Stack.size();

  // manipulate stack of up to 40 strings
  stringStack.push("hello");
  std::cout << stringStack.top() << '\n';
  //返回类型为:int
  auto size2 = stringStack.size();

  /*
    1.可知size1和size2是不同的类型
    2.std::is_same参考"附录D的D.3.3接"
      c++11写法:
        std::is_same<decltype(size1), decltype(size2)>::value
  */
  if (!std::is_same_v<decltype(size1), decltype(size2)>/*c++17*/) {
    std::cout << "size types differ" << '\n';
  }
}
