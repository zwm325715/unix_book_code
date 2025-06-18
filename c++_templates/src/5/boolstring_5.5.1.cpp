#include "boolstring_5.5.1.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
    //C++ 标准库中的一个 I/O 操纵符（manipulator），用于控制布尔值在输入/输出流中的格式。
    //  输出时：将布尔值转换为文本形式（true 或 false），而不是数字形式（1 或 0）
    std::cout << std::boolalpha;

    BoolString s1("hello");
    std::cout << s1.get<>() << std::endl; //hello
    std::cout << s1.get<bool>() << std::endl; //false

    BoolString s2("on");
    std::cout << s2.get<>() << std::endl; //on
    std::cout << s2.get<bool>() << std::endl;//true
}