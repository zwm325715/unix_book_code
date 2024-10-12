#include "stack1_2.1.hpp"

// partial specialization of class Stack<> for pointers:
// 针对指针类型的类模板Stack<>的部分特化(偏特化)
template<typename T>
class Stack<T*> {
  private:
    std::vector<T*> elems;    // elements 存的是指针类型

  public:
    void push(T*);            // push element
    T* pop();                 // pop element
    T* top() const;           // return top element
    bool empty() const {      // return whether the stack is empty
        return elems.empty();
    }
};

template<typename T>
void Stack<T*>::push (T* elem) {
    elems.push_back(elem);    // append copy of passed elem
}

template<typename T>
T* Stack<T*>::pop () {
    assert(!elems.empty());
    T* p = elems.back();
    elems.pop_back();         // remove last element
    return p;                 // and return it (unlike in the general case)
}

template<typename T>
T* Stack<T*>::top () const {
    assert(!elems.empty());
    return elems.back();      // return copy of last element
}
