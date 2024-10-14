#include <iostream>

//为了结束递归:在参数包为空时调用本函数(非模版函数重载版本)
void print (){}
//变参模版:可接受任意数量，类型不同的实参
template<typename T, typename... Types>
void print (T firstArg, Types... args/*参数包*/){
  std::cout << firstArg << '\n'; 
  /*
    递归调用print(...)处理其余实参
  */
  print(args...); 
}
