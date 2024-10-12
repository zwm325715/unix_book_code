#include <iostream>
//1.前置声明Stack<T>
template<typename T>
class Stack;
//2.前置声明operator<<为一个模版
template<typename T>
std::ostream& operator<<(std::ostream&,const Stack<T>&);

template<typename T>
class Stack {
    /*
    3.将上面的operator<<函数声明为友元，operator<<必须要有<T>
    注意:
        <T>在operator<<之后,则相当于我们声明了一个"非成员函数模版的特化"作为友元
        如果没有<T>,则相当于声明一个"新的非模版函数"(12.5.2)
    */
    friend/*关注点*/ std::ostream& operator<< <T>/*关注点*/ (std::ostream&,const Stack<T>&);
};