#include "stack1_2.1.hpp"
#include <iostream>
#include <string>

int main() {
  Stack<int/*显示指定模版实参*/> intStack;  // stack of ints
  Stack<std::string> stringStack;  // stack of strings

  // manipulate(/məˈnɪpjuleɪt/ v.操作,使用) int stack
  intStack.push(7);
  std::cout << intStack.top() << '\n';

  // manipulate string stack 使用string类型的栈
  stringStack.push("hello");
  std::cout << stringStack.top() << '\n';
  stringStack.pop();
}
