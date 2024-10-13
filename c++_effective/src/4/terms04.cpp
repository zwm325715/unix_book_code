#include <iostream>

void f1() {
    //对"int"进行手工初始化
    int x = 0;
    //对"指针"进行手工初始化
    const char * text = "A C-style string";
    //以读取input stream的方式完成初始化
    double d;
    std::cin >> d;
}

class ABEntry {
private:
    std::string _name;
    int _age;
public:
    ABEntry();
    ABEntry(const std::string & name);
};

// ABEntry::ABEntry(const std::string & name) {
//     //这是赋值(assignment),而非初始化(initialization)
//     _name = name;
// }

//成员初值列:这些都是初始化
ABEntry::ABEntry(const std::string & name)
    /*
		1.初值列中针对各个成员变量而设的实参,
    	  被拿去作为各成员变量之构造函数的实参.
    	2.准确的说，本例中的_name以name为初值进行copy构造
    	*/
        :_name(name) {
	//本地不需要有动作了
}

//default构造
ABEntry::ABEntry()
        //调用_name的default构造函数
        :_name(),
        //内置int类型显示初始化为0
        _age(0) {
};


class ABEntry02 {
private:
    const int _cvar;
    std::string & _refvar;
public:
    ABEntry02();
};

std::string myString = "Initial value";
//default构造
ABEntry02::ABEntry02()
        //OK：const类型的成员变量通过初值方式初始化
        :_cvar(100),
         _refvar(myString){
    _cvar = 300;//NO
    _refvar = myString;//NO
};

class FileSystem {...};
//定义了local static对象的函数，返回一个reference指向该对象
FileSystem& tfs() {
    static FileSystem fs;
    return fs;
}
    



