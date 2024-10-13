#include "deduce2_2.9.hpp"
int main () {
    //c++17开始推导为Stack<int>
    Stack intStack = 3;

    /*
    由于构造函数是引用类型传参，参数类型不会退化
    所以对于字符数组来讲T推导结果就是原型Stack<char[7]>
    */
    Stack stringStack = "bootom";
    
}