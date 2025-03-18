#include <stdio.h>

// callee 函数，返回一个整数
int callee(int value) {
    return value * 2; // 简单地将输入值乘以2后返回
}

// 主函数，展示如何在 switch 语句中使用 callee 函数
void test_switch() {
    int x = 3;

    // 在 switch 条件判断中调用 callee 函数
    switch (callee(x)) {
        case 1: // case 1*2 = 2
            printf("Case 2 matched: %d\n", callee(1));
            break; // 没有使用 {}

        case 2: // case 2*2 = 4
            printf("Case 4 matched: %d\n", callee(2));
            // 使用 {}
            {
                int result = callee(2);
                printf("Nested block in case 4: %d\n", result);
            }
            break;

        case 3: // case 3*2 = 6
            printf("Case 6 matched: %d\n", callee(3));
            // 没有使用 {}
            if (1) // 只是为了演示，这里可以是任何条件
                printf("Another statement without braces in case 6\n");
            break;

        default:
            printf("Default case: %d\n", callee(x));
            // 使用 {}
            {
                int result = callee(x);
                printf("Nested block in default case: %d\n", result);
            }
            break;
    }
}

int main() {
    // 调用测试 switch 语句的函数
    test_switch();

    return 0;
}