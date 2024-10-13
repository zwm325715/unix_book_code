
#include <unistd.h>
#include <iostream>
class RegisterImpl;
// Register是个指针类型
typedef RegisterImpl* Register;

//RegisterImpl * c_rarg0 = 7
//"整数"可以直接强制转换为"任何类的指针类型"
const Register c_rarg0 = (Register)7/*强转为指针类型*/;

class RegisterImpl {
  friend class A;
private:
  void test() {

  }  
public:    
  //当前地址对应的int
  int encoding() const { 
    return (intptr_t)this; 
  }
};

class A {
public:
   void a() {
      RegisterImpl * impl = new RegisterImpl();
      impl->test();//加上friend后就可以访问私有方法了
   }
};

int main() {
    //7
    std::cout << c_rarg0->encoding() <<std::endl;
}