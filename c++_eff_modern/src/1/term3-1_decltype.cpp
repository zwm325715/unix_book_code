#include "term3-1_decltype.hpp"
//2
bool f(const Widget& w){
    decltype(w)/* const Widget & */ w1 = w;
    return true;
};

int main() {
    decltype(i)/* const int */ i_type{0}; //1

    //2
    Widget w;
    decltype(w)/* class Widget */ s;
    decltype(f)/* bool(const Widget &) */ f_type;
    f_type(s);
    decltype(f(s))/* bool */ f_res_type;

    //3
    decltype(Point::x)/* int */ x_type;
    decltype(Point::y)/* int */ y_type;

    //4.
    int t0 = 0;
    my_vector<int> v;
    decltype(v)/*my_vector<int>*/ v_type;
    decltype(v[0])/* int & */ v0 = t0 ;
}