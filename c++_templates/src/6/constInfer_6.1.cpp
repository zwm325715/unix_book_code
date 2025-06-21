#include <iostream>
using namespace std;
//1.按值传递:"顶层const"被忽略
template<typename T>
void foo(T param) {}

//2.按引用传递: const被保留(确保引用不能修改原始常量对象)
template<typename T>
void bar(T& param) {}

int main() {
    const int x = 42;
    foo(x); //T被推导为int

    //传指针: "底层const"保留;"顶层const"被忽略
    const int* ptr = nullptr;
    foo(ptr); //T被推导为const int*

    int* const ptr2 = nullptr;
    foo(ptr2); // T被推导为int*

    const int y = 10;
    bar(y); //T被推导为const int
}