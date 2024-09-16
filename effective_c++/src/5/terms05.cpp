class Empty {
public: 
    //default构造函数
    Empty() { }
    //copy构造函数
    Empty(const Empty& rhs){}
    //析构函数
    ~Empty() {}

    //copy assignment操作符
    Empty& operator= (const Empty& rhs){};
};