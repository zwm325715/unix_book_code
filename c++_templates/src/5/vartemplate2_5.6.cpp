#include <array>
#include <iostream>
#include <ostream>
//1.变量模版:默认的模版实参
template<typename T = long double>
constexpr T pi = T {3.1415926535897932385};

//2.变量模版:通过"非类型参数"参数化,"非类型参数"也可以用于初始化器的参数化
template<int N>
std::array<int,N> arr{}; //包含N个元素的数组,零初始化;是全局作用域的数组变量

template<auto N>
constexpr decltype(N) dval = N;  //dval的类型取决于传递值

int main(int argc, char *argv[]) {
    std::cout << pi<> << std::endl;
    std::cout << pi<float> << std::endl;
    std::cout << "------------------" << std::endl;

    arr<10>[0] = 42;  //设置全局数组arr的第1个元素
    for(std::size_t i = 0; i < arr<10>.size(); i++) {
        std::cout << arr<10>[i] << std::endl;
    }

    std::cout << "------------------" << std::endl;
    std::cout << dval<'c'> << std::endl; //N是值'c'的char类型


}
