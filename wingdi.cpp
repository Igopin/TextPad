/* Window message processing file */

#include "window.h"

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  static window wnd;

  switch (message)  /* handle the messages */
  {
  case WM_CREATE:
    wnd.WMCreate(hwnd, message, wParam, lParam);
    break;
  case WM_PAINT:
    wnd.WMPaint(hwnd, message, wParam, lParam);
    break;
  case WM_SIZE:
    wnd.WMSize(hwnd, message, wParam, lParam);
    break;
  case WM_COMMAND:
    wnd.WMCommand(hwnd, message, wParam, lParam);
    break;
  case WM_VSCROLL:
    wnd.WMVScroll(hwnd, message, wParam, lParam);
    break;
  case WM_HSCROLL:
    wnd.WMHScroll(hwnd, message, wParam, lParam);
    break;
  case WM_KEYDOWN:
    wnd.WMKeydown(hwnd, message, wParam, lParam);
    break;
  case WM_DESTROY:
    wnd.WMDestroy(hwnd, message, wParam, lParam);
    break;
  default:
    return DefWindowProc(hwnd, message, wParam, lParam);
  }
  return 0;
} /* End of 'WindowProcedure' function */

/* END OF 'wingdi.cpp' FILE */
