#include <string>
#include <unordered_set>

class Customer {
private:
    std::string name;
public:
    Customer(std::string const& n) : name(n) { }
    std::string getName() const { return name; }
};

struct CustomerEq {
    //仿函數
    bool operator() (Customer const& c1, Customer const& c2) const {
        return c1.getName() == c2.getName();
    }
};

struct CustomerHash {
    //仿函數
    std::size_t operator() (Customer const& c) const {
        return std::hash<std::string>()(c.getName());
    }
};

// define class that combines operator() for variadic base classes:
// 为变参基类定义组合运算符operator():
//   定义一个派生自变参基类的类,并从每个基类引入其operator()声明
template<typename... Bases>
struct Overloader : Bases.../*变参基类*/ {
    using Bases::operator()...;  // OK since C++17
};

int main() {
    // combine hasher and equality for customers in one type:
    // 在一个类中组合了Customer的哈希和比较运算:
    //    利用using特性从CustomerHash和CustomerEq中派生CustomerOP,并能使用2个基类的仿函数
    using CustomerOP = Overloader<CustomerHash,CustomerEq>;

    std::unordered_set<Customer,CustomerHash,CustomerEq> coll1;
    std::unordered_set<Customer,CustomerOP,CustomerOP> coll2;
    //...
}