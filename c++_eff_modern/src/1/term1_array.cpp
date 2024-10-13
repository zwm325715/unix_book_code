#include "term1_array.hpp"
#include <array>
//name的类型为const char[11]
const char name[] = "J.P.Briggs";
//ptrToName的类型为const char *，可见数组可退化成指针
const char * ptrToName = name;

int main () {
    /*
    1."按值传递函数模版"的"数组类型"将被推导成"指针类型"
    2.此时T被推导成const char *
        template <> void f1<const char *>(const char *param)
    */
    f1(name);

    /*
    1."按引用传递函数模版"的"数组类型"将被推导成"真实数组类型"
    2.此时T被推导成const char [11]
        template <> void f2<const char[11]>(const char &param[11])
    */
    f2(name);

    int keyVals[] = {1,3,7,9,11,22,35};
    //声明一个数组时，指定其尺寸和另一个数组相同
    int mappedVals[myArraySize(keyVals)];//编译期就可以确定大小,类型为:int[7]
    std::array<int, myArraySize(keyVals)/*也是7*/> stdArray;
}
