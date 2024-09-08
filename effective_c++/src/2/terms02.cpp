#include <iostream>
// ASPECT_RATIO 有可能没进入符号表(symbol table)中，
// 因此在碰到错误时，提示信息不会有ASPECT_RATIO名
#define ASPECT_RATIO 1.653
//解决:用常量替换宏
const double AspectRatio = 1.653;//必进入符号表


const char * const authorName = "Scott Meyers";
const std::string authorName("Scott Meyers");

class GamePlayer {
private:
    //常量声明式
    static const int NumTurns = 5;
    //使用该常量
    int scores[NumTurns];
};

const int GamePlayer::NumTurns;


//放在头文件
class CostEstimate {
private:
    //static类型的"class专属常量"声明
    static const double FudgeFactor;
};
//放在实现文件内
const double CostEstimate::FudgeFactor=1.35;


class EnumHack {
private:
    static const int NumTurns;
    enum {
        num = 5
    };
    //使用该常量
    int scores[num];
};
const int EnumHack::NumTurns = 5;

#define CALL_WITH_MAX(a,b) f((a)>(b) ? (a) : (b))

//由于不知道T是什么，所以形参采用pass by reference-to-const
template<typename T>
inline void callWithMax(const T& a,const T& b) {
    f( a>b ? a : b );
}