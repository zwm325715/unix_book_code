#pragma once
#include <string>
#include <iostream>

class Person {
  private:
    std::string name;
  public:
    // generic constructor for passed initial name:
    // 传入实参初始化成员name的泛型构造函数
    template<typename STR>
    explicit Person(STR&& n) : name(std::forward<STR>(n)) {
        std::cout << "Template-CONSTR for '" << name << "'\n";
    }

    // copy and move constructor:
    Person (Person const& p) : name(p.name) {
        std::cout << "COPY-CONSTR Person '" << name << "'\n";
    }
    //临时方案
    // Person (Person & p) : name(p.name) {
    //     std::cout << "COPY-CONSTR2 Person '" << name << "'\n";
    // }
    Person (Person&& p) : name(std::move(p.name)) {
        std::cout << "MOVE-CONSTR Person '" << name << "'\n";
    }
};
