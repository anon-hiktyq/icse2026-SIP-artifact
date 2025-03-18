#include <stdio.h>
#include <string.h>

// 定义全局变量
int global_var = 42;

// 定义结构体
struct Person {
    char name[50];
    int age;
    float height;
};

// 定义联合体
union Data {
    int i;
    float f;
    char str[20];
};

// 定义枚举
enum Weekday {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

// 定义一个包含各种类型的函数
void test_function(int param1, char *param2, struct Person *person_ptr) {
    // 局部变量
    int local_var = param1 + global_var;
    printf("局部变量 local_var: %d\n", local_var);

    // 使用形参
    printf("形参 param2: %s\n", param2);

    // 操作结构体
    if (person_ptr != NULL) {
        printf("结构体 person_ptr->name: %s, 年龄: %d, 身高: %.2f\n",
               person_ptr->name, person_ptr->age, person_ptr->height);
    }

    // 操作联合体
    union Data data;
    data.i = 100;
    printf("联合体 data.i: %d\n", data.i);

    data.f = 3.14159;
    printf("联合体 data.f: %.5f\n", data.f);

    strcpy(data.str, "Hello Union");
    printf("联合体 data.str: %s\n", data.str);

    // 操作枚举
    enum Weekday today = TUESDAY;
    printf("今天是: ");
    switch (today) {
        case MONDAY:   printf("星期一\n"); break;
        case TUESDAY:  printf("星期二\n"); break;
        case WEDNESDAY:printf("星期三\n"); break;
        case THURSDAY: printf("星期四\n"); break;
        case FRIDAY:   printf("星期五\n"); break;
        case SATURDAY: printf("星期六\n"); break;
        case SUNDAY:   printf("星期日\n"); break;
        default:       printf("未知\n"); break;
    }

    // 操作数组
    int arr[5] = {1, 2, 3, 4, 5};
    printf("数组 arr: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 操作指针
    int num = 42;
    int *ptr = &num;
    printf("指针 ptr 指向的值: %d\n", *ptr);

    // 修改全局变量
    global_var += 10;
    printf("修改后的全局变量 global_var: %d\n", global_var);
}

int main() {
    // 初始化结构体
    struct Person person = {"Alice", 30, 1.65};

    // 调用测试函数
    test_function(10, "Hello, World!", &person);

    return 0;
}