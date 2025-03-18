#include <stdio.h>

// 定义funb，它接受一个整数并返回该整数加1的结果
int funb(int x) {
    return x + 1;
}

// 定义funa，它接受一个整数并打印该整数
void funa(int y) {
    printf("The result is: %d\n", y);
}

// 测试样例
int main() {
    int value = 5;

    // 调用funa，将funb(value)的结果作为参数传入
    funa(funb(value));

    // 这里等价于以下两步：
    // int temp = funb(value); // 先执行funb，得到结果6
    // funa(temp);            // 然后将结果作为参数传给funa

    return 0;
}