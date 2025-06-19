#include <vector>

#include "stack7decl_5.5.hpp"

int main(int argc, char *argv[]) {
    //error: wrong number of template arguments (0, should be at least 1)
    //Stack<int, std::vector<> > oldStack_Error;//编译报错
    Stack<int, std::vector<int> > oldStack_OK;//编译报错
}
