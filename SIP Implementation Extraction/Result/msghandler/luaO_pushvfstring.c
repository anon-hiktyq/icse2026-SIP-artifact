#include "luaO_pushvfstring.h"
void luaO_pushvfstringFun(void *p) 
{
    luaO_pushvfstring *pIp = (luaO_pushvfstring*)p;
  BuffFS buff;  /* holds last part of the result */
  const char *e;  /* points to next '%' */
  {IPCALL(initbuff,ipinitbuff_0,.L = pIp->L,.buff = &buff);}
  while ((e = strchr((pIp->fmt), '%')) != NULL) {
    {addstr2buff(&buff, pIp->fmt, ct_diff2sz(e - pIp->fmt));}  /* add 'fmt' up to '%' */
    switch (*(e + 1)) {  /* conversion specifier */
      case 's': {  /* zero-terminated string */
        const char *s = va_arg((pIp->argp), char *);
        if (s == NULL) s = "(null)";
        {IPCALL(addstr2buff,ipaddstr2buff_1,.buff = &buff,.str = s,.slen = strlen(s));}
        break;
      }
      case 'c': {  /* an 'int' as a character */
        char c;{c = cast_char(va_arg(pIp->argp, int));}
        {IPCALL(addstr2buff,ipaddstr2buff_0,.buff = &buff,.str = &c,.slen = sizeof(char));}
        break;
      }
      case 'd': {  /* an 'int' */
        TValue num;
        {setivalue(&num, va_arg(pIp->argp, int));}
        {IPCALL(addnum2buff,ipaddnum2buff_0,.buff = &buff,.num = &num);}
        break;
      }
      case 'I': {  /* a 'lua_Integer' */
        TValue num;
        {setivalue(&num, cast(lua_Integer, va_arg(pIp->argp, l_uacInt)));}
        {IPCALL(addnum2buff,ipaddnum2buff_2,.buff = &buff,.num = &num);}
        break;
      }
      case 'f': {  /* a 'lua_Number' */
        TValue num;
        {setfltvalue(&num, cast_num(va_arg(pIp->argp, l_uacNumber)));}
        {IPCALL(addnum2buff,ipaddnum2buff_1,.buff = &buff,.num = &num);}
        break;
      }
      case 'p': {  /* a pointer */
        char bf[LUA_N2SBUFFSZ];  /* enough space for '%p' */
        void *p = va_arg((pIp->argp), void *);
        int len;{len = lua_pointer2str(bf, LUA_N2SBUFFSZ, p);}
        {addstr2buff(&buff, bf, cast_uint(len));}
        break;
      }
      case 'U': {  /* an 'unsigned long' as a UTF-8 sequence */
        char bf[UTF8BUFFSZ];
        int len;{int luaO_utf8esc_ret_0; IPCALL(luaO_utf8esc,ipluaO_utf8esc_0,.buff = bf,.x = va_arg(pIp->argp, unsigned long),.pIp->ret = &luaO_utf8esc_ret_0);len = luaO_utf8esc_ret_0;}
        {addstr2buff(&buff, bf + UTF8BUFFSZ - len, cast_uint(len));}
        break;
      }
      case '%': {
        {IPCALL(addstr2buff,ipaddstr2buff_4,.buff = &buff,.str = "%",.slen = 1);}
        break;
      }
      default: {
        {IPCALL(addstr2buff,ipaddstr2buff_2,.buff = &buff,.str = e,.slen = 2);}  /* keep unknown format in the result */
        break;
      }
    }
    (pIp->fmt) = e + 2;  /* skip '%' and the specifier */
  }
  {IPCALL(addstr2buff,ipaddstr2buff_3,.buff = &buff,.str = pIp->pIp->fmt,.slen = strlen(pIp->fmt));}  /* rest of 'fmt' */
  const char * clearbuff_ret_0;IPCALL(clearbuff,ipclearbuff_0,.buff = &buff,.ret = clearbuff_ret_0);pIp->ret =  clearbuff_ret_0;  /* empty buffer into a new string */
}