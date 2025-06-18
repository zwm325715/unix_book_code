#include <iostream>
#include <ostream>

#include "difCompVarTemplate1_5.6.hpp"

//编译单元2
void print() {
    std::cout << val<long> << std::endl;
    std::cout << val<std::string> << std::endl;
}
