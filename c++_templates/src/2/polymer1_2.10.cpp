#include "polymer1_2.10.hpp"

int main () {
    //1.定义一个参数value类型的聚合体
    ValueWithComment<int> vc;
    vc.value = 42;
    vc.comment = "intial value";

    /*
    2.使用推导指引，推导为ValueWithComment<std::string>
      如果没有推导指引,ValueWithComment将不可能初始化,因为其没有
      对应可进行实参推导的构造函数
    */
    ValueWithComment vc2 {"hello","intial value"};
}
