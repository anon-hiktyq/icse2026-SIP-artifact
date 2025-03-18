// utils.h
#ifndef UTILS_H
#define UTILS_H

#include "types.h"

// 声明一个函数，返回两个整数的和
int add(int a, int b);

// 声明一个函数，打印一个 Point 结构体
void print_point(const Point *p);

// 声明一个函数，根据颜色枚举值打印颜色名称
void print_color(Color color);

// 声明一个全局变量（不使用 extern）
extern int global_var;  // 注意：这里我们不需要使用 extern，因为我们在 utils.c 中直接定义了它

#endif // UTILS_H