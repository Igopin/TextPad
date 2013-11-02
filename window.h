/* Window class header file header file */

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "defines.h"
#include "text.h"

/* Window processing class */
class window
{
private:
  char *file_path;     /*  Path file to load                       */

  int
    max_str_len,
    start_str_pos,     /* Offset string pointer to draw            */
    vert_scrlb_step,   /* Scrollbar step (if number of string more */
                       /* than maximal scroll range)               */
    num_win_str;

  int stat_parts[2];

  HDC  hDC;
  PAINTSTRUCT ps;
  CREATESTRUCT *cs;
  HMENU hMenu;
  OPENFILENAME OpenFName;
  HWND hStatWnd;
  HWND hProgBar;

  VEC2
    client_field,  /* Client size field */
    win_size;      /* Windows size      */

  HFONT hFont;

  WINTEXT txt;
public:

  /* Default constructor */
  window( void ): max_str_len(0), start_str_pos(0), vert_scrlb_step(1), num_win_str(0)
  {
    stat_parts[0] = 300;
    stat_parts[1] = -1;
    txt.SetFontSize(hDC, 10, 21);
    //txt.SetFontColor(hDC, RGB(0, 0, 0), RGB(0, 255, 0));
  };

  /* WM_CREATE message processing */
  void WMCreate(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

  /* WM_SIZE message processing */
  void WMSize(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

  /* WM_PAINT message processing */
  void WMPaint(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

  /* WM_MOUSEMOVE message processing */
  void WMMouseMove(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

  /* WM_COMMAND message processing */
  void WMCommand(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

  /* WM_KEYDOWN message processing */
  void WMKeydown(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

  /* WM_VSCROLL message processing */
  void WMVScroll(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

  /* WM_HSCROLL message processing */
  void WMHScroll(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

  /* WM_DESTROY message processing */
  void WMDestroy(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

  /* Main class destructor */
  ~window()
  {
    //DeleteObject(h)
    if (file_path != NULL && file_path[0] != 0)
      delete file_path;
  };
};
#endif /* _WINDOW_H_ */

/* END OF 'wingdi.h' FILE */
