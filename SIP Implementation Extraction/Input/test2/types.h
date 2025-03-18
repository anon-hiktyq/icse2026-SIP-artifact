// types.h
#ifndef TYPES_H
#define TYPES_H

// 使用 typedef 定义一个新的类型
typedef unsigned int uint;



// 定义一个结构体 Point
typedef struct {
    int x;
    int y;
} Point;

// 定义一个联合体 Data
typedef union {
    int i;
    float f;
    char c;
} Data;

// 定义一个枚举 Color
typedef enum {
    RED,
    GREEN,
    BLUE
} Color;

#endif // TYPES_H