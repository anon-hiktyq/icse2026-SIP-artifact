#include <stdio.h>
#include "common.h"
#include "global_vars.h"
#include "callees.h"

// 定义一个未使用的全局变量
extern int unusedGlobalVar;

// 主函数
int main() {
    // 初始化变量
    int modifiedValue = getModifiedValue(); // 调用返回普通变量的 callee
    Color color = getColorBasedOnFlag();   // 调用返回普通变量的 callee

    // 打印结果
    printf("Modified Value: %d\n", modifiedValue);
    printf("Selected Color: %d\n", color);

    // 修改全局变量
    globalFlag = 2;
    color = getColorBasedOnFlag();
    printf("Updated Color: %d\n", color);

    return 0;
}