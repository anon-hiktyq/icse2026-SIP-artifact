#include "luaV_concat.h"
void luaV_concatFun(void *p) 
{
    luaV_concat *pIp = (luaV_concat*)p;
  if ((pIp->total) == 1)
    return;  /* "all" values already concatenated */
  do {
    StkId top = (pIp->L)->top.p;
    int n = 2;  /* number of elements handled in this pass (at least 2) */
    {if (!(ttisstring(s2v(top - 2)) || cvt2str(s2v(top - 2))) ||
        !tostring(pIp->L, s2v(top - 1)))
      {IPCALL(luaT_tryconcatTM,ipluaT_tryconcatTM_0);}  /* may invalidate 'top' */
    else {if (isemptystr(s2v(top - 1)))  /* second operand is empty? */
      {cast_void(tostring(pIp->L, s2v(top - 2)));}  /* result is first operand */
    else {if (isemptystr(s2v(top - 2))) {  /* first operand is empty string? */
      {setobjs2s(pIp->L, top - 2, top - 1);}  /* result is second op. */
    }
    else {
      /* at least two non-empty string values; get as many as possible */
      size_t tl;{tl = tsslen(tsvalue(s2v(top - 1)));}
      TString *ts;
      /* collect total length and number of strings */
      for (n = 1; n < (pIp->total) && tostring((pIp->L), s2v(top - n - 1)); n++) {
        size_t l;{l = tsslen(tsvalue(s2v(top - n - 1)));}
        {if (l_unlikely(l >= MAX_SIZE - sizeof(TString) - tl)) {
          (pIp->L)->top.p = top - (pIp->total);  /* pop strings to avoid wasting stack */
          {IPCALL(luaG_runerror,ipluaG_runerror_0);}
        }}
        tl += l;
      }
      if (tl <= LUAI_MAXSHORTLEN) {  /* is result a short string? */
        char buff[LUAI_MAXSHORTLEN];
        {IPCALL(copy2buff,ipcopy2buff_0,.top = top,.n = n,.buff = buff);}  /* copy strings to buffer */
        {TString * luaS_newlstr_ret_0;IPCALL(luaS_newlstr,ipluaS_newlstr_0,.ret = luaS_newlstr_ret_0);ts = luaS_newlstr_ret_0;}
      }
      else {  /* long string; copy strings directly to final result */
        {TString * luaS_createlngstrobj_ret_0;IPCALL(luaS_createlngstrobj,ipluaS_createlngstrobj_0,.ret = luaS_createlngstrobj_ret_0);ts = luaS_createlngstrobj_ret_0;}
        {copy2buff(top, n, getlngstr(ts));}
      }
      {setsvalue2s(pIp->L, top - n, ts);}  /* create result */
    }}}}
    (pIp->total) -= n - 1;  /* got 'n' strings to create one new */
    (pIp->L)->top.p -= n - 1;  /* popped 'n' strings and pushed one */
  } while ((pIp->total) > 1);  /* repeat until only 1 result left */
}