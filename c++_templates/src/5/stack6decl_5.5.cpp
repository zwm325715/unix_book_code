#include "stack6decl_5.5.hpp"
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

//实现模版赋值运算符
template<typename T>
 template<typename T2>
Stack<T>& Stack<T>::operator= (Stack<T2> const& op2) {
    elems.clear();                        // remove existing elements
    //这里要访问op2的所有成员(elems)
    elems.insert(elems.begin(),           // insert at the beginning
                 op2.elems.begin(),       // all elements from op2
                 op2.elems.end());
    return *this;
}

int main(int argc, char *argv[]) {
    Stack<int> intStack1,intStack2;
    intStack1.push(11);
    std::cout << "intStack1起始: " << intStack1.top() << std::endl;

    intStack2.push(22);
    Stack<float> floatStack;
    floatStack.push(33.0);
    std::cout << "floatStack起始: " << floatStack.top() << std::endl;

    intStack1 = intStack2;
    std::cout << "intStack1被赋值为intStack2: " << intStack1.top() << std::endl;

    floatStack = intStack1;
    std::cout << "floatStack被赋值为intStack1: " << floatStack.top() << std::endl;
}

