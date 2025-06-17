//专门处理"原始数组或字符串字面量"的模版:N和M在调用时可被推导出来
template<typename T/*数组或字符串*/, int N, int M>
bool less (T(&a)[N]/*注意有中括号*/, T(&b)[M]) {
    for (int i = 0; i<N && i<M; ++i) {
        if (a[i]<b[i]) return true;
        if (b[i]<a[i]) return false;
    }
    return N < M;
}

//专门处理"字符串字面量"的模版
// template<int N, int M>
// bool less (char const(&a)[N], char const(&b)[M]) {
//     for (int i = 0; i<N && i<M; ++i) {
//         if (a[i]<b[i]) return true;
//         if (b[i]<a[i]) return false;
//     }
//     return N < M;
// }

