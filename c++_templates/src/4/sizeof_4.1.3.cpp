#include <iostream>
//必须声明:为结束递归 而 重载的无参非模版函数
void print() {
    std::cout << "********非模版print**********" << std::endl;
}

//变参模版
template<typename T, typename... Types>
void print (T firstArg, Types... args) {
    std::cout << "剩余类型的个数:" << sizeof... (Types) << std::endl;
    std::cout << "剩余实参的个数:" << sizeof... (args) << std::endl;
    std::cout << "----------------------------------" << std::endl;
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

int main(int argc, char *argv[]) {
    print(1,"zwm","dtt");
}
