#include <utility>
#include <string>
#include <iostream>

class Person {
  private:
    std::string name;
  public:
    // constructor for passed initial name: 传递初始化成员name的构造函数
    explicit Person(std::string const& n) : name(n) {
        std::cout << "copying string-CONSTR for '" << name << "'\n";
    }

    explicit Person(std::string&& n) : name(std::move(n)) {
        std::cout << "moving string-CONSTR for '" << name << "'\n";
    }

    // copy and move constructor: 拷贝和移动构造函数
    Person (Person const& p) : name(p.name) {
        std::cout << "COPY-CONSTR Person '" << name << "'\n";
    }

    Person (Person&& p) : name(std::move(p.name)) {
        std::cout << "MOVE-CONSTR Person '" << name << "'\n";
    }
};

int main() {
  std::string s = "sname";
  // init with string object => calls copying string-CONSTR (Constructor的简写)
  // 使用字符串对象初始化 => 调用拷贝字符串的构造函数
  Person p1(s);

  // init with string literal => calls moving string-CONSTR
  // 使用字符串字面量初始化 => 调用移动字符串的构造函数
  Person p2("tmp");

  // copy Person => calls COPY-CONSTR
  // 拷贝Person对象 => 调用 拷贝构造函数
  Person p3(p1);

  // move Person => calls MOVE-CONST
  // 移动Person对象 => 调用移动构造函数
  Person p4(std::move(p1));
}
