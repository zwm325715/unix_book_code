#include <iostream>
#include <string>

//1.编译错误:浮点数不能作为非类型模版参数
template<double VAT>
double process(double v) {
    return v*VAT;
}

//2.编译错误:"类类型的对象"不能作为非类型模版参数
template<std::string name>
class myClass{
};

//3.对象的指针或引用作为模版实参
template<const char * name>
class myClass2{};

//4.非类型模版参数的实参可以是任何编译期表达式
template<int I,bool B>
class C {};