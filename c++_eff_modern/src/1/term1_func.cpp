#include "term1_array.hpp"

void someFunc(int,double);

int main() {
    /*
      1."按值"传递函数时，也会退化成 "函数指针"
      2.T推导为 void (*)(int, double)
        template <> 
        void f1<void (*)(int, double)>(void (*param)(int, double))
    */
    f1(someFunc);

    /*
      1."按引用"传递函数时，不会退化，保持原样
      2.T推导为 void(int, double)
        template <> 
        void f2<void(int, double)>(void (&param)(int, double))
    */
    f2(someFunc);
}