#include <iostream>

void print() {
   std::cout << "********空print**********" << std::endl;
}
//变参模版
template<typename T, typename.../*类型是个变参:注意这里的省略号*/ Types>
void print (T firstArg, Types... args) {
    std::cout << "接收到的参数值:" << firstArg << std::endl;
    //C++11开始提供
    if (sizeof...(args) > 0) {
        /**
        原因：
            1.是否使用实例化代码是在运行期决定，而是否调用则是在编译期决定的。
            2.在最后一个实参调用print()函数模版，print(args...)的调用语句仍会实例化为无参函数,
              如果没有提供print()就会报错
        */
        print(args...);
    }
}

template<typename... T>
void printDoubled(T const&... args) {
    //变参表达式:
    //  不仅仅是转发了所有参数,还可以进行计算=>将每个参数args加倍,并传递给print()函数
    print( (args + args) ... );//建议使用小括号包裹，避免不必要的麻烦
}

//编译期表达式
template<typename T1, typename... TN>
//判断所有实参的类型是否相同
constexpr bool isHomogeneous(T1,TN...) {
    //是个一元右折叠表达式:  &&是op操作符(逻辑与运算); ...是语法;  std::is_same<T1,TN>::value是pack
    return (std::is_same<T1,TN>::value && ...);//C++17起
}

int main(int argc, char *argv[]) {
    printDoubled(1,2,3,4,5);

    // 返回值的表达式扩展为:
    //  std::is_same<int,int>::value && std:: std::is_same<int,char const*>::value
    std::cout << "返回假:" << isHomogeneous(43,-1,"hello") << std::endl;
    // 实参类型都被推导为char const*,因为是传值会导致退化
    std::cout << "返回真:" << isHomogeneous("hello"," ","world","!") << std::endl;
}
