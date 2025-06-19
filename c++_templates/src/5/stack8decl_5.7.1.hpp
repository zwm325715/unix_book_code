#pragma once
#include <deque>

//c++11 报错:expected a template of type ‘template<class Elem> class Cont’,
//  got ‘template<class _Tp, class _Alloc> class std::vector’
template<typename T,
         template<typename Elem,
                  typename Alloc=std::allocator<Elem> /*变通*/>
         class Cont = std::deque>
class Stack {
  private:
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
