// utils.c
#include <stdio.h>
#include "utils.h"

// 定义一个全局变量
int global_var = 42;

// 实现 add 函数
int add(int a, int b) {
    return a + b;
}

// 实现 print_point 函数
void print_point(const Point *p) {
    if (p != NULL) {
        printf("Point: (%d, %d)\n", p->x, p->y);
    } else {
        printf("Point is NULL\n");
    }
}

// 实现 print_color 函数
void print_color(Color color) {
    switch (color) {
        case RED:
            printf("Color: RED\n");
            break;
        case GREEN:
            printf("Color: GREEN\n");
            break;
        case BLUE:
            printf("Color: BLUE\n");
            break;
        default:
            printf("Unknown color\n");
            break;
    }
}