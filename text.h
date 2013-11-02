/* Text class header file */

#ifndef _TEXT_H_
#define _TEXT_H_

#include <windows.h>
#include <iostream>
#include "defines.h"
#include "list.h"

/* Main text support class */
class WINTEXT
{
private:
  char *str_buf;    /* File buffer */
  VEC2 font_size;
  LIST str_list;    /* String list */
  HFONT hFont;

public:
  int
    num_of_str,     /* Num of string in file */
    max_str_len;    /* Maximal string length */

  /* Default constructor */
  WINTEXT( void ) : str_buf(NULL), num_of_str(0), max_str_len(0){};

  /* Get font function */
  HFONT & GetFont( void ){ return hFont; };

  /* Get font size function */
  VEC2 GetFontSize( void ){return font_size; };

  /* Get num of string function */
  int GetNumOfStr( void ){ return num_of_str; };

  /* Set font size function */
  void SetFontSize( HDC &hDC, int sym_w, int sym_h )
  {
    font_size = VEC2(sym_w, sym_h);
    hFont = CreateFont(sym_h, sym_w, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                       ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                       DEFAULT_QUALITY, FF_MODERN, NULL);
  };

  /* Set font color function */
  void SetFontColor( HDC &hDC, COLORREF bkg_font_color, COLORREF font_color )
  {
    //SetTextColor(hDC, font_color);
    //SetBkColor(hDC, bkg_font_color);
  };

  /* Set next start text position function */
  LIST &operator++( int );

  /* Set previous start text position function */
  LIST &operator--( int );

  /* Set start text position function */
  void operator+=( int i );

  /* Set previous start text position function */
  void operator-=( int i );

  /* Load file function */
  int LoadFile( char *file_name );

  /* Draw text function */
  void Draw( HDC &hDC, int start_str_pos, VEC2 &client_f );

  /* Reset text system function */
  void Reset( void )
  {
    str_list.Free();
    if (str_buf != NULL)
      delete str_buf;
    num_of_str = 0;
    max_str_len = 0;
  }

  /* Destructor */
  ~WINTEXT()
  {
    DeleteObject(hFont);
    str_list.Free();
    if (str_buf != NULL)
      delete str_buf;
  };
};

#endif /* _TEXT_H_ */

/* END OF 'list.h' FILE */
