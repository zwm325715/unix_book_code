#pragma once
#include <string>

class BoolString {
  private:
    std::string value;
  public:
    BoolString (std::string const& s)
     : value(s) {
    }

    template<typename T = std::string>
    T get() const {  // get value (converted to T)
      return value;
    }

    /**
     error: explicit specialization in non-namespace scope ‘class BoolString’
     这个错误表明你试图在类作用域（class BoolString 内部）进行模板显式特化，而 C++ 不允许这样做。
     显式特化必须在命名空间作用域（全局或命名空间内）进行。

    template<>
    inline bool BoolString::get<bool>() const;
    */
};


// full specialization for BoolString::getValue<>() for bool
// 为成员函数模版提供一个全局特化版本
template<>
//由于是在头文件中定义的全局特化，为了避免该定义可能被不同编译单元包含而引发的重复定义错误，所以定义成了inline的形式
inline bool BoolString::get<bool>() const {
  return value == "true" || value == "1" || value == "on";
}
