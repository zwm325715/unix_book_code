#include <iostream>
using namespace std;

//按"值"方式传递形参的模版
template<typename T>
void f1(T param){
    cout<<param<<endl;
};

//按"引用"方式传递形参的模版
template<typename T>
void f2(T& param) {
    cout<<param<<endl;
};

/*
    以"编译期常量"形式返回数组的大小
    (该数组形参未起名字，因为我们不关心它)
*/
template<typename T,std::size_t N>
constexpr std::size_t myArraySize(T(&)[N]) noexcept {
    return N;
}