#include <iostream>
#include <type_traits>
//1.模板类型约束
template <typename T>
void modifyData(T& value) {
    static_assert(!std::is_const_v<T>, "Cannot modify const data");
    // ... 修改操作 ...
}

//2.条件编译
template <typename T>
void process(T& value) {
    if constexpr (std::is_const_v<T>) {
        std::cout << "Processing CONST type\n";
        // 只读操作
    } else {
        std::cout << "Processing mutable type\n";
        // 可修改操作
    }
}

int main(int argc, char *argv[]) {
    // 检查基本类型
    static_assert(std::is_const_v<const int>);     // true
    static_assert(!std::is_const_v<int>);          // false

    // 检查指针类型（注意const位置）
    static_assert(!std::is_const_v<const int*>);   // false（底层const:指针本身不是const）
    static_assert(std::is_const_v<int* const>);    // true（底层const:指针本身是const）
    static_assert(std::is_const_v<const int* const>); // true

    // 检查引用类型（引用本身无const概念）
    static_assert(!std::is_const_v<const int&>);   // false
    static_assert(!std::is_const_v<int&&>);        // false

    std::cout << "-------------模板类型约束------------------" << std::endl;
    int a = 10;
    const int b = 20;

    modifyData(a);  // OK
    //modifyData(b);  // 编译错误：static_assert失败

    std::cout << "-------------条件编译------------------" << std::endl;
    process(a); //Processing mutable type
    process(b); //Processing CONST type
}
