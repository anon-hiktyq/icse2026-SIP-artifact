#ifndef MODULE_H
#define MODULE_H

// 声明一个外部全局变量
extern int global_var;

// 声明一个带有 volatile 修饰符的外部全局变量
extern volatile int volatile_global_var;

extern int global_var2;

// 函数原型
void set_global_var(int value);
int get_global_var(void);

void set_volatile_global_var(int value);
int get_volatile_global_var(void);

#endif // MODULE_H