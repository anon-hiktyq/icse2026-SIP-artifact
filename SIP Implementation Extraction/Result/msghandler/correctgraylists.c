#include "correctgraylists.h"
void correctgraylistsFun(void *p) 
{
    correctgraylists *pIp = (correctgraylists*)p;
  GCObject **list = correctgraylist(&g->grayagain);
  *list = (pIp->g)->weak; (pIp->g)->weak = NULL;
  {GCObject ** correctgraylist_ret_3;IPCALL(correctgraylist,ipcorrectgraylist_3,.p = list,.ret = correctgraylist_ret_3);list = correctgraylist_ret_3;}
  *list = (pIp->g)->allweak; (pIp->g)->allweak = NULL;
  {GCObject ** correctgraylist_ret_2;IPCALL(correctgraylist,ipcorrectgraylist_2,.p = list,.ret = correctgraylist_ret_2);list = correctgraylist_ret_2;}
  *list = (pIp->g)->ephemeron; (pIp->g)->ephemeron = NULL;
  {GCObject ** correctgraylist_ret_1;IPCALL(correctgraylist,ipcorrectgraylist_1,.p = list,.ret = correctgraylist_ret_1);correctgraylist_ret_1;}
}