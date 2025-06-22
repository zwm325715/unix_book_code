#include "specialmemtmpl2_6.2.hpp"

int main() {
    std::string s = "sname2";
    Person p1(s);//正常

    Person p2("tmp2");//正常(此时p2的构造不会创建临时字符串,STR推导为char const[4])

    //Person p3(p1);//错误

    const Person p4_const("const_tmp2");//常量Person对象
    Person p4C(p4_const);//拷贝Person的常量对象 =>正常:拷贝构造

    Person p5(std::move(p1));//正常:移动构造
}
