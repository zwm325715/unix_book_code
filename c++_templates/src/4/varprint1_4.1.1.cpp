#include "varprint1_4.1.1.hpp"
#include <string>
int main() {
    std::string s("world");
    /*
        print<double,const char *,std::string>(7.5,"hello",s);
        ->
            print<const char *,std::string>("hello",s);
                ->
                    print<std::string>(s);
                        ->
                            print(); //结束递归
    */
    print(8.5,"hello",s);
}