#include "insertkey.h"
void insertkeyFun(void *p) 
{
    insertkey *pIp = (insertkey*)p;
  Node mp;{Node * mainpositionTV_ret_0; IPCALL(mainpositionTV,ipmainpositionTV_0,.t = pIp->t,.key = pIp->key,.ret = mainpositionTV_ret_0);mp = mainpositionTV_ret_0;}
  /* table cannot already contain the key */
  {const TValue * getgeneric_ret_0;IPCALL(getgeneric,ipgetgeneric_0,.t = pIp->t,.key = pIp->key,.deadok = 0,.ret = getgeneric_ret_0);lua_assert(isabstkey(getgeneric(pIp->t, pIp->key, 0)));}
  {if (!isempty(gval(mp)) || isdummy(pIp->t)) {  /* main position is taken? */
    Node *othern;
    Node f;{Node * getfreepos_ret_0; IPCALL(getfreepos,ipgetfreepos_0,.t = pIp->t,.ret = getfreepos_ret_0);f = getfreepos_ret_0;}  /* get a free place */
    if (f == NULL)  /* cannot find a free place? */
      *(pIp->ret) =  0;
    {lua_assert(!isdummy(pIp->t));}
    {Node * mainpositionfromnode_ret_0;IPCALL(mainpositionfromnode,ipmainpositionfromnode_0,.t = pIp->t,.nd = mp,.ret = mainpositionfromnode_ret_0);othern = mainpositionfromnode_ret_0;}
    if (othern != mp) {  /* is colliding node out of its main position? */
      /* yes; move colliding node into free position */
      while (othern + gnext(othern) != mp)  /* find previous */
        {othern += gnext(othern);}
      {gnext(othern) = cast_int(f - othern);}  /* rechain to point to 'f' */
      *f = *mp;  /* copy colliding node into free pos. (mp->next also goes) */
      {if (gnext(mp) != 0) {
        {gnext(f) += cast_int(mp - f);}  /* correct 'next' */
        {gnext(mp) = 0;}  /* now 'mp' is free */
      }}
      {setempty(gval(mp));}
    }
    else {  /* colliding node is in its own main position */
      /* new node will go into free position */
      {if (gnext(mp) != 0)
        {gnext(f) = cast_int((mp + gnext(mp)) - f);}  /* chain new position */
      else {lua_assert(gnext(f) == 0);}}
      {gnext(mp) = cast_int(f - mp);}
      mp = f;
    }
  }}
  {setnodekey(mp, pIp->key);}
  {lua_assert(isempty(gval(mp)));}
  setobj2t(cast(lua_State *, 0), gval(mp), value);
  *(pIp->ret) =  1;
}