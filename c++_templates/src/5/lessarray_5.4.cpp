#include "lessarray_5.4.hpp"

#include <iostream>
#include <ostream>

int main(int argc, char *argv[]) {
    int x[] = {1,2,3};
    int y[] = {1,2,3,4,5};

    //原始数组:实例化less<>()后,T为int类型,N为3,M为5.
    // 等价于std::cout << less<int,3,5>(x,y) << std::endl;
    std::cout << less(x,y) << std::endl;

    //原始字符串字面量:实例化less<>()后,T为char const类型,N为3,M为4
    std::cout << less("ab","abc") << std::endl;
}
