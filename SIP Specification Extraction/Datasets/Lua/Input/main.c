#include "main.h"
void mainFun(main *pIp) 
{
    int value = 5;

    // 调用funa，将funb(value)的结果作为参数传入
    {IPCALL(funa,ipfuna,.y = funb(value));}

    // 这里等价于以下两步：
    // int temp = funb(value); // 先执行funb，得到结果6
    // funa(temp);            // 然后将结果作为参数传给funa

    *(pIp -> ret) = 0;
}