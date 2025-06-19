#include "vartemplate_5.6.1.hpp"

#include <iostream>
#include <ostream>
using namespace  std;

//变量模版:允许为MyClass<>的不同特化版本定义不同的值
template<typename T>
int myMax = MyClass<T>::max;

//延伸:STL中的模版类数据成员的变量模版
template<typename T>
constexpr bool isSigned = std::numeric_limits<T>::is_signed;

int main(int argc, char *argv[]) {
    //应用程序可以写成这个样子
    auto i = myMax<int>;
    //等价于
    auto j = MyClass<int>::max;
    cout << "i=" << i << ",j=" << j << endl;

    std::cout << std::boolalpha;
    cout << "is_signed=" << isSigned<char> <<  endl;
}
