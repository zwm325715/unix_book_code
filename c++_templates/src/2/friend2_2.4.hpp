#include <iostream>

template<typename T>
class Stack {
    template<typename U>
    friend std::ostream& operator<<(std::ostream&,const Stack<U>&);
};