#include "stack3_2.7.hpp"
#include <iostream>
#include <deque>

//1.使用关键字typedef
typedef Stack<int> IntStack1;

//2.使用关键字using,从c++11开始
using IntStack2 = Stack<int>;

//3.别名模版
template<typename T>
using DequeStack = Stack<T,std::deque<T>>;


//4.声明一个类模板
template<typename T>
struct MyType {
    using interator = T;    
};

//定义成员类型的别名模版
template<typename T>
using MyTypeIterator_t = typename MyType<T>::interator;