#pragma once
#include <deque>

template<typename T>
class Stack {
  private:
    std::deque<T> elems;       // elements

  public:
    void push(T const&);       // push element
    void pop();                // pop element
    T const& top() const;      // return top element
    bool empty() const {       // return whether the stack is empty
        return elems.empty();
    }

    // assign stack of elements of type T2
    template<typename T2>
    Stack& operator= (Stack<T2> const&);

    // to get access to private members of Stack<T2> for any type T2
    //   访问任何元素类型为T2的Stack<T2>的私有成员
    // 由于elems是私有的,因此需要声明所有其他Stack实例为其(T2)友元:
    //    由于没有使用模版参数的名称,因此可以省略掉名称
    template<typename> friend class Stack;
};