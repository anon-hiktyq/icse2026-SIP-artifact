#ifndef COMMON_H
#define COMMON_H

// 使用 typedef 定义 struct
typedef struct {
    int x;
    float y;
} Point;

// 直接定义 struct
struct Rectangle {
    Point topLeft;
    Point bottomRight;
};

// 使用 typedef 定义 union
typedef union {
    int intValue;
    float floatValue;
} ValueUnion;

// 定义 enum
typedef enum {
    RED,
    GREEN,
    BLUE
} Color;

#endif // COMMON_H