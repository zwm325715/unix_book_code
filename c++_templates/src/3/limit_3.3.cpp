#include "limit_3.3.hpp"

extern const char s03[] = "hi";//外部链接
const char s11[] = "hi";//内部链接

int main() {
    //编译错误：不允许使用字符串字面量
    myClass2<"hello"> x1;
    //OK：所有版本
    myClass2<s03> x2;
    //OK：从C++11开始
    myClass2<s11> x3;

    static const char s17[] = "hi"; //无链接
    myClass2<s17> x4; //OK：从C++17

    C<sizeof(int)+4,sizeof(int)==4> c;//OK
    C<42,sizeof(int)>4> c1;//编译错误：第一个>就终止了模版实参列表
    C<42,(sizeof(int)>4)> c2;//OK


}