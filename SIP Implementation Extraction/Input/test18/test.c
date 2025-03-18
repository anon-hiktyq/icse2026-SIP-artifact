#include <stdio.h>

// callee 函数，返回一个整数
int callee(int value) {
    return value * 2; // 简单地将输入值乘以2后返回
}

// 主函数，展示如何在条件判断中使用 callee 函数
void test_conditions() {
    int a = 5;
    int b = 10;

    // 第一个条件判断，条件和执行体都有 callee 调用，且没有使用 {}
    if (callee(a) > callee(b))
        printf("First condition met: %d is greater than %d\n", callee(a), callee(b));

    // 第二个条件判断，条件和执行体都有 callee 调用，并使用了 {}
    if (callee(a) <= callee(b)) {
        printf("Second condition met: %d is less or equal to %d\n", callee(a), callee(b));
        // 可以在这里添加更多语句
    }
}

int main() {
    // 调用测试条件的函数
    test_conditions();

    return 0;
}