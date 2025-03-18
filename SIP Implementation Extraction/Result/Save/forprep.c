#include "forprep.h"
void forprepFun(void *p) 
{
    forprep *pIp = (forprep*)p;
  TValue *pinit = s2v(pIp -> ra);
  TValue *plimit = s2v(pIp -> ra + 1);
  TValue *pstep = s2v(pIp -> ra + 2);
  if (ttisinteger(pinit) && ttisinteger(pstep)) { /* integer loop? */
    lua_Integer init = ivalue(pinit);
    lua_Integer step = ivalue(pstep);
    lua_Integer limit;
    if (step == 0)
      {IPCALL(luaG_runerror,ipluaG_runerror_0);}
    {int forlimit_ret_0;IPCALL(forlimit,ipforlimit_0,.L = pIp->L,.init = init,.lim = plimit,.p = &limit,.step = step,.ret = pIp->&forlimit_ret_0);if ((forlimit_ret_0)
      *(pIp -> ret) = 1; /* skip the loop */
    else {  /* prepare loop counter */
      lua_Unsigned count;
      if (step > 0) {  /* ascending loop? */
        count = l_castS2U(limit) - l_castS2U(init);
        if (step != 1)  /* avoid division in the too common case */
          count /= l_castS2U(step);
      }
      else {  /* step < 0; descending loop */
        count = l_castS2U(init) - l_castS2U(limit);
        /* 'step+1' avoids negating 'mininteger' */
        count /= l_castS2U(-(step + 1)) + 1u;
      }
      /* use 'chgivalue' for places that for sure had integers */
      chgivalue(s2v(pIp -> ra), l_castU2S(count));  /* change init to count */
      setivalue(s2v(pIp -> ra + 1), step);  /* change limit to step */
      chgivalue(s2v(pIp -> ra + 2), init);  /* change step to init */
    }}
  }
  else {  /* try making all values floats */
    lua_Number init; lua_Number limit; lua_Number step;
    if (l_unlikely(!tonumber(plimit, &limit)))
      luaG_forerror(pIp -> L, plimit, "limit");
    if (l_unlikely(!tonumber(pstep, &step)))
      luaG_forerror(pIp -> L, pstep, "step");
    if (l_unlikely(!tonumber(pinit, &init)))
      luaG_forerror(pIp -> L, pinit, "initial value");
    if (step == 0)
      luaG_runerror(pIp -> L, "'for' step is zero");
    if (luai_numlt(0, step) ? luai_numlt(limit, init)
                            : luai_numlt(init, limit))
      *(pIp -> ret) = 1; /* skip the loop */
    else {
      /* make sure all values are floats */
      setfltvalue(s2v(pIp -> ra), limit);
      setfltvalue(s2v(pIp -> ra + 1), step);
      setfltvalue(s2v(pIp -> ra + 2), init);  /* control variable */
    }
  }
  *(pIp -> ret) = 0;
}