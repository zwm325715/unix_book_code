#include "deduce3_2.9.hpp"
int main () {
    /*
    1.此时编译报错,报错信息如下:
      No viable(/ˈvaɪəb(ə)l/ adj.可行的) conversion from 
     'const char[7]' to 'Stack<std::string>' (aka 'Stack<basic_string<char>>')
    2.原因:
        根据语言规则,不能通过将 "字符串字面量" 传递给
        期望接收std::string类型的构造函数来 "拷贝初始化(符号=)对象".
        但是可以通过{}方式进行初始化
    */
    // Stack stringStack = "bootom"; 编译报错
    Stack stringStack { "bootom" };//OK：推导为Stack<std::string>
}