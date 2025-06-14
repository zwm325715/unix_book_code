// define binary tree structure and traverse helpers:
struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int i=0) : value(i), left(nullptr), right(nullptr) {
    }
    //...
};
auto left = &Node::left;
auto right = &Node::right;

// traverse tree, using "fold expression(折叠表达式)":
template<typename T, typename... TP>
Node *traverse(T np, TP... paths) {
    //使用运算符 ->* 遍历二叉树的路径
    //下面的是折叠表达式:从np开始遍历paths中所有可变元素
    return (np->*...->*paths); // np ->* paths1 ->* paths2 ...
}

int main() {
    // init binary tree structure:
    Node *root = new Node{0};
    root->left = new Node{1};
    root->left->right = new Node{2};
    //...
    // traverse binary tree:
    Node *node = traverse(root, left, right);
    //...
}
