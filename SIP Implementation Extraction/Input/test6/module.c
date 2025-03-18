#include <stdio.h>
#include "module.h"

// 定义全局变量
int global_var = 0;
int global_var2 = 0;

// 定义带有 volatile 修饰符的全局变量
volatile int volatile_global_var = 0;

// 设置全局变量的值
void set_global_var(int value) {
    global_var = value;
}

// 获取全局变量的值
int get_global_var(void) {
    return global_var;
}

// 设置带有 volatile 修饰符的全局变量的值
void set_volatile_global_var(int value) {
    volatile_global_var = value;
}

// 获取带有 volatile 修饰符的全局变量的值
int get_volatile_global_var(void) {
    return volatile_global_var;
}