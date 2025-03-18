#include <stdio.h>

// 定义一个整型数组作为全局变量
int globalIntArray[5] = {1, 2, 3, 4, 5};

// 定义一个指向整型的指针数组作为全局变量
int value0 = 10;
int value1 = 20;
int value2 = 30;
int *globalPointerArray[3] = {&value0, &value1, &value2};

void printGlobalVariables() {
    // 打印整型数组的内容
    printf("Contents of globalIntArray:\n");
    for(int i = 0; i < 5; ++i) {
        printf("globalIntArray[%d] = %d\n", i, globalIntArray[i]);
    }

    // 打印指针数组的内容
    printf("\nContents of globalPointerArray:\n");
    for(int i = 0; i < 3; ++i) {
        printf("globalPointerArray[%d] points to value: %d\n", i, *globalPointerArray[i]);
    }
}

int main() {
    // 调用函数打印全局变量的内容
    printGlobalVariables();

    // 修改通过指针数组访问的数据并再次打印验证修改结果
    *globalPointerArray[1] = 25;
    printf("\nAfter modifying the second element pointed by globalPointerArray:\n");
    printGlobalVariables();

    return 0;
}