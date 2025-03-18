
#include "main.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  assigns *(pIp->ret);
  ensures *(pIp->ret) == 0;
*/
void mainFun(main *pIp) 
{
    int value = 5;

    // 调用funa，将funb(value)的结果作为参数传入
    /*@
      assigns \nothing; // Assuming funb and funa do not modify any global state
    */
    {IPCALL(funa,ipfuna,.y = funb(value));}

    // 这里等价于以下两步：
    // int temp = funb(value); // 先执行funb，得到结果6
    // funa(temp);            // 然后将结果作为参数传给funa

    *(pIp -> ret) = 0;
}
