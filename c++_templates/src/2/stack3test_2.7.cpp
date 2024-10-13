#include "stack3_2.7.hpp"
#include <iostream>
#include <deque>

int main() {
  //int类型的Stack,第二个模版参数采用默认值
  Stack<int> intStack;

  //double类型的Stack,使用std::deque<>来管理
  Stack<double,std::deque<double>> dblStack;

  // manipulate int stack
  intStack.push(7);
  std::cout << intStack.top() << '\n';
  intStack.pop();

  // manipulate double stack
  dblStack.push(42.42);
  std::cout << dblStack.top() << '\n';
  dblStack.pop();
}
