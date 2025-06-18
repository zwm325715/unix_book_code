#include "stack5decl_5.5.hpp"
#include <iostream>
#include <ostream>

template<typename T>
void Stack<T>::pop() {
    elems.pop_front();
}

template<typename T>
T const& Stack<T>::top() const {
    return elems.front();
}

template<typename T>
void Stack<T>::push(T const & t) {
    elems.push_back(t);
}

template<typename T>
/**
  定义成员模版的语法:
   a)不能写到T中的template<>中，必须另起一行
   b)表达的含义是: "模版参数为T的模版内部" 定义了 "模版参数为T2"的内部模版
 */
template<typename T2>
Stack<T>& Stack<T>::operator= (Stack<T2> const& op2) {//重载=运算符
    // create a copy of the assigned stack  生成一个赋值栈的副本
    Stack<T2> tmp(op2);//直接丢Stack
    // remove existing elements 移除现存元素
    elems.clear();
    // copy all elements 拷贝所有元素
    while (!tmp.empty()) {
        elems.push_front(tmp.top());
        tmp.pop();
    }
    return *this;
};


int main(int argc, char *argv[]) {
    Stack<int> intStack1,intStack2;
    intStack1.push(1);
    std::cout << "intStack1起始: " << intStack1.top() << std::endl;

    intStack2.push(2);
    Stack<float> floatStack;
    floatStack.push(3.0);
    std::cout << "floatStack起始: " << floatStack.top() << std::endl;

    intStack1 = intStack2;
    std::cout << "intStack1被赋值为intStack2: " << intStack1.top() << std::endl;

    floatStack = intStack1;
    std::cout << "floatStack被赋值为intStack1: " << floatStack.top() << std::endl;
}