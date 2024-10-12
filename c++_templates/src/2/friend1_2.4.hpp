#include <iostream>

template<typename T>
class Stack {
    void printOn(std::ostream & strm) const {
        strm << "1111";
    }
    /*
        1.不加friend时会报错:
          Overloaded 'operator<<' must be a binary operator (has 3 parameters)
          这个问题一般是在类内编写重载运算符的时候遇到，解决办法:
           -如果想使其变为一个友元函数，加friend关键字
           -不希望变为友元函数时，那么就将其在"类的外部"进行声明
          该提示信息的原因:
            一个成员函数(没有friend时)需要隐式的获取第一个参数,这就导致在类内
            编写重载二元运算符的成员函数的时候传递了3个参数。
        2.知识点
          因为二元运算符重载(binary operator overloading)以"某个类的成员函数"形式实现时,
          左运算符必然为该类型(*this).
          一般的重载是对称的,比如重载了obj+int(可以是成员函数)，也要重载int+obj(只能以非成员函数出现)
          使用friend是为了让该函数可以访问Stack的非public成员.
    */
    friend std::ostream& operator<<(std::ostream& strm,const Stack<T>& s) {
        s.printOn(strm);
        return strm;
    }
};