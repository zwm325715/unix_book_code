#include <deque>

template<typename T, typename Cont = std::deque<T> /*参数化内部的容器类型*/>
class Stack {
  private:
    //Cont<T> elems; 编译会报错，因为不是个模版
    Cont elems;                // elements

  public:
    void push(T const&);       // push element
    void pop();                // pop element
    T const& top() const;      // return top element
    bool empty() const {       // return whether the stack is empty
        return elems.empty();
    }

    // assign stack of elements of type T2
    template<typename T2, typename Cont2>
    Stack& operator= (Stack<T2,Cont2> const&);
    // to get access to private members of Stack<T2> for any type T2:
    template<typename, typename> friend class Stack;
};
