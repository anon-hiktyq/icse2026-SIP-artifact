// main.c
#include <stdio.h>
#include "utils.h"

int main() {
    // 使用 typedef 定义的类型
    uint number = 100;
    printf("Unsigned int: %u\n", number);

    // 使用 struct Point
    Point p = {5, 10};
    print_point(&p);

    // 使用 union Data
    Data data;
    data.i = 42;
    printf("Data as int: %d\n", data.i);

    data.f = 3.14;
    printf("Data as float: %.2f\n", data.f);

    data.c = 'A';
    printf("Data as char: %c\n", data.c);

    // 使用 enum Color
    Color my_color = GREEN;
    print_color(my_color);

    // 调用 add 函数
    int result = add(5, 7);
    printf("5 + 7 = %d\n", result);

    // 使用全局变量
    printf("Global variable: %d\n", global_var);

    return 0;
}