#include "term3-2_decltype.hpp"
#include <deque>
int main() {
    std::deque<int> d;
    /*
    1.编译失败:
        Expression is not assignable
    2.原因:
        函数模版中(d[5])返回的是int&,但是通过auto类型推导后将去掉引用(&)饰词，
        也就是返回值类型变成了int.
        该int是个右值，因此不能将10赋予它.
    */
    authAndAccess2(d, 5) = 10;

    //OK，返回的是int&了，可以进行赋值了
    authAndAccess3(d,5) = 10;

    //decltype(auto)用在变量声明
    Widget w;
    const Widget& cw = w;
    //类型为Widget
    auto myWidget1 = cw;
    //类型为const Widget &
    decltype(auto) myWidget2 = cw;
}