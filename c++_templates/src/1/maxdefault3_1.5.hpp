template<typename T1, typename T2>
auto max (T1 a, T2 b) {
  return  b < a ? a : b;
}

template<typename RT, typename T1, typename T2>
RT max (T1 a, T2 b) {
  return  b < a ? a : b;
}

auto a = ::max(4,7.2); //使用第1个模版
auto b = ::max<long double>(7.2,4);  //使用第2个模版

/*
  1.编译错误:两个函数模版都匹配
    信息:
     Call to 'max' is ambiguous(/æmˈbɪɡjuəs/ adj.有歧义的)
  2.注意4和7.2的顺序，如果互换一下就不会有错误.分析如下
    -(7.2,4)时
      第1个模版:
        double max(double,int)
      第2个模版:
        int max(double,int)
*/
auto c = ::max<int>(4,7.2);