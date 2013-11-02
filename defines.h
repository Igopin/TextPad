/* Support header file */

#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <windows.h>

/* Two compoents vector */
class VEC2
{
public:
  int x, y;
  /* Deafult constructor */
  VEC2( void ): x(0), y(0){};

  /* Value constructoright_v.yr */
  VEC2( int _x, int _y ) : x(_x), y(_y){};

  /* Add operator*/
  VEC2 operator+( const VEC2 &right_v )
  {
    return VEC2(x + right_v.x, y + right_v.y);
  };

  /* Devide operator*/
  VEC2 operator-( const VEC2 &right_v )
  {
    return VEC2(x - right_v.x, y - right_v.y);
  };
};

/* Test git comment */

#endif /* _DEFINES_H_ */


/* END OF 'wingdi.h' FILE */
