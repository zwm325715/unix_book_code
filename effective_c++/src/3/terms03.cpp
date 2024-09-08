#include <iostream>
#include <vector>
#include <string.h>

void f1() {
    std::vector<int> vec;
    vec.push_back(3);
    //1.iter的作用像个 T * const
    const std::vector<int>::iterator iter = vec.begin();
    *iter = 10; //OK
    ++iter;//NO! iter是const

    //2.cIter的作用像个const T *
    std::vector<int>::const_iterator cIter = vec.begin();
    *cIter = 10; //NO! *cIter是const
    ++cIter; //OK
}

class TextBlock {
private:
    std::string _text;
public:
    TextBlock(std::string text):_text(text){};
    //operator[] for const对象
    const char& operator[](std::size_t position) const {
        return _text[position];
    }

    //operator[] for non-const对象
    char& operator[](std::size_t position) {
        return _text[position];
    }
};

void f2() {
    TextBlock tb("Hello");
    //调用non-const TextBlock::operator[]
    std::cout << tb[0];//OK
    tb[0] = 'x'; //OK

    const TextBlock ctb("World");
    //调用const TextBlock::operator[]
    std::cout << ctb[0];//OK
    //NO!返回的是const char &类型,不允许实行赋值动作
    ctb[0] = 'x'; 
}

//此函数中ctb是const
void print(const TextBlock & ctb) {
    //调用const TextBlock::operator[]
    std::cout << ctb[0];
}

class CTextBlock {
private:
    char * _pText;
    //mutable修饰的成员变量即使在const成员函数内也是可以被修改的
    mutable bool _isValid;
public:
    CTextBlock(char * text):_pText(text){};
    /*
      1.bitwise const声明，但此时其实不适当   
      2.函数返回了一个char的引用：指向了对象内部的值
    */
    char & operator[](std::size_t position)  const {//编译器认为OK
        return _pText[position];
    }

    void print() const {
        std::cout << this->_pText <<std::endl;
    }
    //const成员函数
    std::size_t length() const;
};

std::size_t CTextBlock::length() const {
    _isValid = true;
    return 100;
};

void f3() {
    char * m = (char *)::malloc(sizeof("Hello"));
    strcpy(m,"Hello");
    const CTextBlock cctb(m);//声明一个常量对象
    //返回类型是个char的引用，因此&取地址后就是char *
    char * pc = &cctb[0];//调用的const operator[]取得一个指针 
    *pc = 'J';//cctb现在就有了'Jello'这样的内容
    //Jello
    cctb.print();
}


class TextBlock01 {
private:
    std::string text;
public:
    const char & operator[](std::size_t position) const {
        //一堆逻辑
        return text[position];
    }

    char & operator[](std::size_t position){
        //一堆逻辑(跟上面的一样)
        return text[position];
    }
};


class TextBlock02 {
private:
    std::string text;
public:
    const char & operator[](std::size_t position) const {
        //共用的逻辑
        return text[position];
    }

    char & operator[](std::size_t position){
        //注意:non-const operator[]内部不能只是单纯调用operator[],这样会递归自己
        //(*this)[position];//NO!
        //将op[]返回值的const移除
        return const_cast<char &>(
                    //为*this加上const是为了去调用const operator[]
                    static_cast<const TextBlock02 &>(*this)[position]
               );//OK
    }
};

int main() {
    f3();
}