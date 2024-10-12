#include <cstring>

//2个任意类型:传引用
template<typename T>
T const& max (T const& a, T const& b) {
  return  b < a ? a : b;
}

//C-string:传值
char const* max (char const* a, char const* b) {
  return std::strcmp(b,a) < 0  ? a : b;
}

//3个任意类型:传引用
template<typename T>
T const& max (T const& a, T const& b, T const& c) {
  /*
    1.error if max(a,b) uses call-by-value
      错误: 如果max(a,b)使用传值调用时就会出错      
    2.编译器提示信息:
      Returning reference to local temporary object  
  */
  return max(max(a,b), c);       
}

int main ()
{
  auto m1 = ::max(7, 42, 68);  // OK

  char const* s1 = "frederic";
  char const* s2 = "anica";
  char const* s3 = "lucas";
  /*
    1.run-time ERROR 运行时错误
    2.因为对于C-strings,max(a,b)创建了一个新的按引用返回的临时局部变量，
      从而留给main()函数的是一个空悬引用
  */
  auto m2 = ::max(s1, s2, s3); 
}
