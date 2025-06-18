#include <deque>

template <typename T>
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

    // assign stack of elements of type T2  使用元素类型为T2的栈来赋值
    template <typename T2>
    Stack&/*返回本体对象*/ operator= (Stack<T2> const&);
};
