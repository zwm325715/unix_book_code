// maximum of two int values:
int max (int a, int b) {
  return  b < a ? a : b;
}

// maximum of two values of any type:
template<typename T>
T max (T a, T b) {
  return  b < a ? a : b;
}

int main() {
  //1.调用非模版max：优先选择非模版函数
  ::max(7, 42);
  /*
    1.重点:模版参数推导不允许"自动类型转换",普通函数参数则是允许的
    2.本次调用使用非模版函数:'a'和42.7都转换为int类型
  */     
  ::max('a', 42.7);      

  //deduction /dɪˈdʌkʃn/ n.推导
  //2.调用模版max
  //模版匹配度更高
  ::max(7.0, 42.0);      // calls max<double> (by argument deduction)
  //模版匹配度更高
  ::max('a', 'b');       // calls max<char> (by argument deduction)
  /*
    显示指定一个空模版实参列表:此语法表明只有模版可以解析此次调用
    所有模版参数都应该从调用实参中推导出来
  */
  ::max<>(7, 42);        // calls max<int> (by argument deduction)
  ::max<double>(7, 42);  // calls max<double> (no argument deduction)
}
