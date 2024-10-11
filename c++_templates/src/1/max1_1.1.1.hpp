/*
  1.关键字typename是类型参数的引导字:
    也可以使用关键字class来代替typename
  2.T是类型参数:
    可以用任意标识符作为类型参数名，习惯上用T
*/
template<typename T>
//类型T也必须是可拷贝的，才能按值返回
T max (T a, T b) {
  //类型T必须支持运算符'<'
  return  b < a ? a : b;
}
