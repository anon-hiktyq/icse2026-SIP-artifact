#include <stdio.h>
#include "common.h"
#include "global_vars.h"
#include "callees.h" // 引入 callee 函数声明

// 定义一个返回普通变量的 callee 函数
int getModifiedValue() {
    int a = 1;
    globalCounter++;
    globalCounter += a; // 修改全局变量
    return globalCounter;
}


// 定义一个返回普通变量的 callee 函数
Color getColorBasedOnFlag() {
    if (globalFlag == 1) {
        return RED;
    } else if (globalFlag == 2) {
        return GREEN;
    } else {
        return BLUE;
    }
}