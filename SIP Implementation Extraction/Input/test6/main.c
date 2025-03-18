#include <stdio.h>
#include "module.h"

int main() {
    // 测试非 volatile 全局变量
    printf("Initial global_var: %d\n", get_global_var());
    set_global_var(42);
    printf("After setting global_var to 42: %d\n", get_global_var());

    // 测试 volatile 全局变量
    printf("Initial volatile_global_var: %d\n", get_volatile_global_var());
    set_volatile_global_var(84);
    printf("After setting volatile_global_var to 84: %d\n", get_volatile_global_var());

    // 模拟可能改变 volatile 变量的事件
    // 这里我们只是再次设置它的值，但在实际应用中，这可能是硬件中断等。
    set_volatile_global_var(168);

    // 注意：由于 volatile 变量不被编译器优化，每次访问都会从内存读取最新值
    printf("After potentially changing volatile_global_var: %d\n", get_volatile_global_var());

    global_var2 ++;

    return 0;
}