
#include <bitset>
#include <iostream>

template<unsigned long  N>
void printBitset(const std::bitset<N> & bs) {
    //调用成员模版,不显示限定模版实参时,编译通过并可运行
    std::cout << bs.to_string() << std::endl;

    std::cout << "----------" << std::endl;
    //编译警告:Dependent template requires using 'template' keyword
    // std::cout << bs.to_string<char,std::char_traits<char>,std::allocator<char>>() << std::endl;
    //解决方案:增加template关键字
    std::cout << bs.template to_string<char,std::char_traits<char>,std::allocator<char>>() << std::endl;
}

int main(int argc, char *argv[]) {
    std::bitset<8> bits; // 8位，初始全0
    bits.set(3, true);// 设置第3位为1(从右向左，索引0开始)

    printBitset(bits);
}
