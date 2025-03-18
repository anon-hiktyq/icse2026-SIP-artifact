#include <stdio.h>

// callee 函数，返回一个整数
int callee(int a, int b) {
    return a + b; // 简单地将两个参数相加后返回
}

// caller 函数，展示了如何在变量初始化时调用 callee 函数
void caller() {
    // 在变量定义时直接调用 callee 函数进行初始化
    int sum = callee(5, 3);

    // 打印结果以验证
    printf("The sum is: %d\n", sum);
}

int main() {
    // 调用 caller 函数来执行我们的测试案例
    caller();

    return 0;
}