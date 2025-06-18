#include <iostream>

class SomeCompilerSpecificName {
    public:
        SomeCompilerSpecificName(); //只有编译期才能调用的构造函数

        //成员模版:重载仿函数
        template <typename T1, typename T2>
        auto operator()(T1 x,T2 y) const {
            return x+y;
        }
};

int main(int argc, char *argv[]) {
    //泛型lambda
    auto lambda_C14 = [](auto x,auto y) {
        return x+y;
    };
    //可以看成是上面类的默认构造对象的快捷表达式
    std::cout << lambda_C14(3,5) << std::endl;
}
