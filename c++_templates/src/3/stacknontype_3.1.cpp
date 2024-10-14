#include "stacknontype_3.1.hpp"
#include <iostream>
#include <string>

int main() {
  /*
    每个模版都实例化出自己的类型
      int20Stack和int40Stack是两种不同的类型，并且
      这2种类型之间不存在隐式或者显示的类型转换.
  */
  Stack<int,20>         int20Stack;     // stack of up to 20 ints
  Stack<int,40>         int40Stack;     // stack of up to 40 ints
  Stack<std::string,40> stringStack;    // stack of up to 40 strings

  // manipulate stack of up to 20 ints
  int20Stack.push(7);
  std::cout << int20Stack.top() << '\n';
  int20Stack.pop();

  // manipulate stack of up to 40 strings
  stringStack.push("hello");
  std::cout << stringStack.top() << '\n';
  stringStack.pop();
}
