#include "stack3_2.7.hpp"
#include <iostream>

int main() {
    Stack<int> intStack1;
    Stack<int> intStack2 = intStack1;//所有版本都正确
    Stack intStack3 = intStack1;//从C++17开始才可以
    
}