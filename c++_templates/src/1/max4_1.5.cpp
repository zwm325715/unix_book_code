#include <iostream>

// 任意类型2个值
template<typename T>
T max (T a, T b) {
  std::cout << "max<T>() \n";
  return  b < a ? a : b;
}

// 任意类型3个值
template<typename T>
T max (T a, T b, T c) {
  
  /*
    1.uses the template version even for ints
      because the following declaration comes too late
      使用模版版本，而不是int类型的普通函数，
      因为下面int类型的函数声明来得太迟了     
  */
  return max (max(a,b), c);  
}                            

// 2个int类型的普通函数:但是顺序在上面3个值调用之后了，因此不会被调用
int max (int a, int b) {
  std::cout << "max(int,int) \n";
  return  b < a ? a : b;
}

int main() {
  /*
    1.OOPS: uses max<T>() instead of max(int,int)   
      哎呀,使用了max<T>(),而不是max(int,int)
  */
  ::max(47,11,33);  
  /*
    测试输出:
      [ob@localhost c++_templates]$ ./bin/1/max4_1.5
      max<T>()
      max<T>()
  */
}
