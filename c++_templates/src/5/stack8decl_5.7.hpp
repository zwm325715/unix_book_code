#pragma once
#include <deque>

template<typename T,
         //第2个参数声明成了类模版:注意有class关键字
         template<class Elem>
         class Cont = std::deque>
class Stack {
  private:
    //这里使用了模版的模版参数T(由第1个模版参数传入的类型T来实例化):
    //  这里这是个特例,一般来说,可以用类模版中的任何类型来实例化模版的模版参数
    Cont<T> elems;             // elements

  public:
    void push(T const&);       // push element
    void pop();                // pop element
    T const& top() const;      // return top element
    bool empty() const {       // return whether the stack is empty
        return elems.empty();
    }
    //...
};
