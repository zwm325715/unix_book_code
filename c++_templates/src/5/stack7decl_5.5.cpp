#include "stack7decl_5.5.hpp"
#include <iostream>
#include <ostream>
#include <vector>

//知识点:当在类模板外部定义成员函数时,不能重复指定模板参数的默认值(默认参数只能在类模板声明中指定一次)
template<typename T,typename Cont/*= std::deque<T> 不能指定默认值*/>
void Stack<T,Cont>::pop() {
    elems.pop_front();
}

template<typename T,typename Cont>
T const& Stack<T,Cont>::top() const {
    return elems.front();
}

template<typename T,typename Cont>
void Stack<T,Cont>::push(T const & t) {
    elems.push_back(t);
}

template<typename T, typename Cont>
 template<typename T2, typename Cont2>
Stack<T,Cont>& Stack<T,Cont>::operator= (Stack<T2,Cont2> const& op2) {
    elems.clear();                        // remove existing elements
    elems.insert(elems.begin(),           // insert at the beginning
                 op2.elems.begin(),       // all elements from op2
                 op2.elems.end());
    return *this;
}

int main(int argc, char *argv[]) {
    Stack<int,std::vector<int>> vStack;
    vStack.push(42);
    vStack.push(7);
    std::cout << "top:" << vStack.top() << std::endl;

    Stack<float,std::vector<float>> floatStack1;
    floatStack1.push(3.2);
    floatStack1 = vStack;
    std::cout << "floatStack1起始: " << floatStack1.top() << std::endl;
}


