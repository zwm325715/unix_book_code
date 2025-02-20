#include <iostream>
using namespace std;
class Test {
public:    
    Test() {
        cout << "构造函数调用!" <<endl;
    }

    ~Test() {
        cout << "~析构函数调用..." <<endl;
    }
};

//测试析构函数调用时机
int main() {
    cout<<"-------case1:会调析构(YES)-------" <<endl;
    {
        Test t1;
    }

    cout<<"-------case2:不会调析构(NO)-------" <<endl;
    Test* t2 = new Test();

    cout<<"-------case3:会调析构(YES)-------" <<endl;
    Test* t3 = new Test();
    delete t3;

    if(true || false && false) {//true
        cout<<"满足条件1" <<endl;
    }
    if(false || true && false) {//false
        cout<<"满足条件2" <<endl;
    }
    if(false || true && true) {//true
        cout<<"满足条件3" <<endl;
    }
    if(true || true && false) {//true
        cout<<"满足条件4" <<endl;
    }
}
/**测试结果
[ob@localhost c++_templates]$ ./bin/4/test
-------case1-------
构造函数调用!
~析构函数调用...
-------case2-------
构造函数调用!
-------case3-------
构造函数调用!
~析构函数调用...
*/