#include <stdio.h>

// 定义一个结构体
typedef struct {
    int x;
    int y;
} Point;

// callee函数，接受结构体、数组、指针及固定值作为参数
void callee(Point p, int arr[], int *ptr, int fixedValue) {
    printf("Point: (%d, %d)\n", p.x, p.y);
    printf("Array values: ");
    for(int i = 0; i < 3; ++i) { // 假设数组长度为3
        printf("%d ", arr[i]);
    }
    printf("\nPointer value: %d\n", *ptr);
    printf("Fixed value: %d\n", fixedValue);
}

int main() {
    // 结构体变量
    Point point = {10, 20};

    // 数组
    int array[] = {1, 2, 3};

    // 指针
    int value = 42;
    int *ptr = &value;

    // 固定值
    int fixedValue = 100;

    // 调用callee函数
    callee(point, array, &value, 100);
    return 0;
}