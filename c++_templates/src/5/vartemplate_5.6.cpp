#include "vartemplate_5.6.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
    //error: missing template arguments before ‘;’ token
    //std::cout << "pi=" << pi;  //编译错误

    //这是2个不同的变量
    std::cout << pi<double> << std::endl;
    std::cout << pi<float> << std::endl;
}
