#include <cstring>
#include <string>

//1.模版函数:任意类型的最大值
template<typename T>
T max (T a, T b) {
  return  b < a ? a : b;
}

//2.模版函数:两个指针
template<typename T>
T* max (T* a, T* b) {
  return *b < *a  ? a : b;
}

//3.普通函数:2个C-strings的最大值
char const* max (char const* a, char const* b) {
  return std::strcmp(b,a) < 0  ? a : b;
}

int main () {
  int a = 7;
  int b = 42;
  //2个int，使用第1个模版函数
  auto m1 = ::max(a,b);

  std::string s1 = "hey";
  std::string s2 = "you";
  //2个string，使用第1个模版函数
  auto m2 = ::max(s1,s2);

  int* p1 = &b;
  int* p2 = &a;
  //2个指针，使用第2个模版函数
  auto m3 = ::max(p1,p2);

  char const* x = "hello";
  char const* y = "world";
  //2个C-string，使用第3个普通函数
  auto m4 = ::max(x,y);
}
