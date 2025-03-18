
#include "luaO_hexavalue.h"

/*@ axiomatic HexaValue {
      predicate is_digit(char c) = '0' <= c <= '9';
      predicate is_lower_hex(char c) = 'a' <= c <= 'f';
      predicate is_upper_hex(char c) = 'A' <= c <= 'F';
      predicate is_xdigit(char c) = is_digit(c) || is_lower_hex(c) || is_upper_hex(c);
      
      logic integer hexa_value(char c) =
        ('0' <= c <= '9') ? (integer)(c - '0') : 
        (('a' <= c <= 'f') ? (integer)(c - 'a' + 10) : (integer)(c - 'A' + 10));
    }
*/

/*@
  requires \valid(pIp);
  requires is_xdigit(pIp->c);
  ensures \result == (char)hexa_value(pIp->c);
  assigns \nothing;
*/
char luaO_hexavalueFun(luaO_hexavalue *pIp) 
{
  lua_assert(lisxdigit(pIp -> c));
  if (lisdigit(pIp -> c)) return cast_byte(pIp -> c - '0');
  else return cast_byte((ltolower(pIp -> c) - 'a') + 10);
}
