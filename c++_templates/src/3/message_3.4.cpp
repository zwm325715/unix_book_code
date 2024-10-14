#include <iostream>
#include "message_3.4.hpp"
//采用任何可能得"非类型参数"的值(c++17)
template<auto T> 
class Message {
  public:
    void print() {
      std::cout << T << '\n'; 
    }
};

int main() {
  // int类型
  Message<42> msg1;
  msg1.print();

  //c++17支持无链接：局部静态字符串
  static char const s[] = "hello";
  // initialize with const char[6] "hello"
  Message<s> msg2;  
  msg2.print(); 
  
  int i;
  MyC<(10)> xxx; //N是int类型引用
}
