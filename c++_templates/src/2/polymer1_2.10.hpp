#include <vector>
#include <string>
#include <iostream>

//模板化聚合体
template<typename T>
struct ValueWithComment {
    T value;
    std::string comment;
};
//从c++17开始，甚至可以为聚合类模版定义推导指引
ValueWithComment(const char*,const char*) -> ValueWithComment<std::string>;