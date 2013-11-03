/* Window processing source file */

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <math.h>

#include "defines.h"
#include "window.h"
#include "resources.h"

const int MAX_RANGE = 65535;  /* Maximal WinGDI scroll range */
const int STAT_BAR_H = 20;    /* Heigth of status bar        */

/* WM_CREATE processing function */
void window::WMCreate(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam)
{
  OpenFName.lStructSize       = sizeof(OPENFILENAME);
  OpenFName.hwndOwner         = hwnd;
  OpenFName.hInstance         = NULL;
  OpenFName.lpstrFilter       = "Text files(*.TXT)\0*.txt\0All Files(*.*)\0*.*\0";
  OpenFName.lpstrCustomFilter = NULL;
  OpenFName.nMaxCustFilter    = 0;
  OpenFName.nFilterIndex      = 0;
  OpenFName.lpstrFile         = NULL;
  OpenFName.nMaxFile          = _MAX_PATH;
  OpenFName.lpstrFileTitle    = NULL;
  OpenFName.nMaxFileTitle     = _MAX_FNAME + _MAX_EXT;
  OpenFName.lpstrInitialDir   = NULL;
  OpenFName.lpstrTitle        = NULL;
  OpenFName.Flags             = 0;
  OpenFName.nFileOffset       = 0;
  OpenFName.nFileExtension    = 0;
  OpenFName.lpstrDefExt       = "txt";
  OpenFName.lCustData         = 0L;
  OpenFName.lpfnHook          = NULL;
  OpenFName.lpTemplateName    = NULL;

  cs = (CREATESTRUCT *)lParam;

  file_path = (char *)cs->lpCreateParams;
  if (file_path[0] != 0)
    txt.LoadFile(file_path);

  win_size = VEC2(cs->cx, cs->cy);
  client_field = VEC2(win_size.x / txt.GetFontSize().x,
                     (win_size.y - STAT_BAR_H) / txt.GetFontSize().y );

  hStatWnd = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
    0, 0, 0, 0, hwnd, NULL, GetModuleHandle(NULL), NULL);
  SendMessage(hStatWnd, SB_SETPARTS, 2, (LPARAM)stat_parts);
  SendMessage(hStatWnd, SB_SETMINHEIGHT, STAT_BAR_H, 0);

  hDC = GetDC(hwnd);
  SelectObject(hDC, txt.GetFont());
  SetTextColor(hDC, RGB(0, 255, 0));
  SetBkColor(hDC, RGB(0, 0, 0));
  ReleaseDC(hwnd, hDC);

} /* End of 'WMCreate' function */

/* WM_PAINT processing function */
void window::WMPaint(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam)
{

  hDC = BeginPaint(hwnd, &ps);
  txt.Draw(hDC, start_str_pos, client_field);
  EndPaint(hwnd, &ps);
} /* End of 'WMPaint' function */


/* WM_SIZE message processing */
void window::WMSize(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam)
{
  int
    delta,          /* */
    cur_vert_pos,
    //cur_horz_pos,
    new_horz_range,
    new_vert_range;
  VEC2 old_client_field;

  win_size.x = LOWORD(lParam);
  win_size.y = HIWORD(lParam);

  cur_vert_pos = GetScrollPos(hwnd, SB_VERT);
  //cur_horz_pos = GetScrollPos(hwnd, SB_HORZ);

  old_client_field = client_field;
  client_field = VEC2(win_size.x / txt.GetFontSize().x,
                      (win_size.y - STAT_BAR_H) / txt.GetFontSize().y);

  /* Vert scrollbar */
  new_vert_range = txt.num_of_str - client_field.y;
  if (new_vert_range < 0)
    new_vert_range = 0;

  if (new_vert_range > MAX_RANGE)
    vert_scrlb_step = (int)(ceil(new_vert_range * 1.0 / MAX_RANGE));

  SetScrollRange(hwnd, SB_VERT, 0, new_vert_range /= vert_scrlb_step, TRUE);
  if (cur_vert_pos > new_vert_range)
    SetScrollPos(hwnd, SB_VERT, new_vert_range, TRUE);

  delta = cur_vert_pos - new_vert_range;
  if (delta > 0)
    txt -= delta * vert_scrlb_step;
  else
    txt += delta * vert_scrlb_step;

  /* Horz scrollbar */
  new_horz_range = max_str_len - client_field.x;
  if (new_horz_range >= 0)
    SetScrollRange(hwnd, SB_HORZ, 0, new_horz_range, TRUE);
  else
    SetScrollRange(hwnd, SB_HORZ, 0, 0, TRUE);

  delta = max_str_len - start_str_pos;
  if (delta < client_field.x)
  {
    start_str_pos -= client_field.x - delta;
    if (start_str_pos < 0)
      start_str_pos = 0;
  }

  SendMessage(hStatWnd, WM_SIZE, wParam, lParam);

  InvalidateRect(hwnd, NULL, TRUE);
} /* End of 'window::WMSize' function */

/* WM_COMMAND message processing */
void window::WMCommand(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam)
{
  int
    horz_range,
    vert_range;
  char
    buf[32],         /* Status bar text buffer */
    file_name[256];

  switch (wParam)
  {
  case IDM_OPEN:
    OpenFName.hwndOwner = hwnd;
    OpenFName.lpstrFile =  file_name;
    OpenFName.lpstrFileTitle = NULL;
    OpenFName.lpstrFile[0] = '\0';
    OpenFName.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;
    GetOpenFileNameA(&OpenFName);
    if (file_name[0] != 0)
    {
      txt.Reset();
      max_str_len = txt.LoadFile(file_name);

      vert_range = txt.num_of_str - client_field.y;
      if (vert_range < 0)
        vert_range = 0;

      if (vert_range > MAX_RANGE)
        vert_scrlb_step = (int)(ceil(vert_range * 1.0 / MAX_RANGE));
      else
        vert_scrlb_step = 1;
      SetScrollRange(hwnd, SB_VERT, 0, vert_range /= vert_scrlb_step, TRUE);
      SetScrollPos(hwnd, SB_VERT, 0, TRUE);
      SetScrollRange(hwnd, SB_HORZ, 0, max_str_len - client_field.x, TRUE);
      SetScrollPos(hwnd, SB_HORZ, 0, TRUE);
      start_str_pos = 0;
      sprintf(buf, "NUM OF STRINGS: %i", txt.GetNumOfStr());
      SendMessage(hStatWnd, SB_SETTEXT, (WPARAM)0, (LPARAM)buf);
      start_str_pos = 0;
    }
    break;
  case IDM_ABOUT:
    MessageBox(hwnd, "Igor Pinaev 2013 33601/1", "About", MB_ICONINFORMATION);
    break;
  case IDM_EXIT:
    SendMessage(hwnd, WM_CLOSE, 0, 0L);
    break;
  }

  InvalidateRect(hwnd, NULL, TRUE);
} /* End of 'window::WMCommand' function */

/* WM_VSCROLL message processing */
void window::WMVScroll(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam)
{
  int
    k,               /* Counter                 */
    cur_pos,         /* Current scroll position */
    new_pos,         /* New scroll position     */
    num_str_to_end;
    char buf[8];
  VEC2 range;

  GetScrollRange(hwnd, SB_VERT, &range.x, &range.y);
  new_pos = cur_pos = GetScrollPos(hwnd, SB_VERT);
  switch(LOWORD(wParam))
  {
  case SB_LINEUP:
    if (new_pos > 0)
    {
      new_pos = cur_pos - 1;
      txt -= vert_scrlb_step;
    }
    break;
  case SB_LINEDOWN:
    if (new_pos < range.y)
    {
      new_pos = cur_pos + 1;
      txt += vert_scrlb_step;
    }
    break;
  case SB_PAGEUP:
    num_str_to_end = cur_pos * vert_scrlb_step;
    if (num_str_to_end > 0)
    {
      if (num_str_to_end > 2 * client_field.y)
      {
        txt -= client_field.y;
        new_pos -= client_field.y / vert_scrlb_step;
      }
      else
      {
        txt -= num_str_to_end;
        new_pos -= num_str_to_end / vert_scrlb_step;
      }
    }
    break;
  case SB_PAGEDOWN:
    num_str_to_end = (txt.num_of_str - cur_pos * vert_scrlb_step)/1;
    if (num_str_to_end > client_field.y)
    {
      if (num_str_to_end > 2 * client_field.y)
      {
        txt += client_field.y;
        new_pos += client_field.y / vert_scrlb_step;
      }
      else
      {
        txt += abs(client_field.y - num_str_to_end);
        new_pos += abs(client_field.y - num_str_to_end) / vert_scrlb_step;
      }
    }
    break;
  case SB_THUMBTRACK:
    new_pos = HIWORD(wParam);
    if ((k = new_pos - cur_pos) > 0)
      txt += abs(k) * vert_scrlb_step;
    else if (k < 0)
      txt -= abs(k) * vert_scrlb_step;
    break;
  }

  sprintf(buf, "%i %%", (int)(cur_pos * 1.0 / range.y * 100));
  SendMessage(hStatWnd, SB_SETTEXT, (WPARAM)1,(LPARAM)buf);

  if (cur_pos != new_pos)
  {
    SetScrollPos(hwnd, SB_VERT, new_pos, TRUE);
    InvalidateRect(hwnd, NULL, TRUE);
  }

} /* End of 'window::WMVScroll' function */

/* WM_HSCROLL message processing */
void window::WMHScroll(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam)
{
  int
    k,            /* Counter                 */
    cur_pos,      /* Current scroll position */
    new_pos;      /* New scroll position     */
  VEC2 max_range;

  cur_pos = new_pos = GetScrollPos(hwnd, SB_HORZ);

  GetScrollRange(hwnd, SB_HORZ, &max_range.x, &max_range.y);

  switch(LOWORD(wParam))
  {
  case SB_LINERIGHT:
    if (cur_pos < max_range.y)
    {
      new_pos = cur_pos + 1;
      start_str_pos++;
    }
    break;
  case SB_LINELEFT:
    if (cur_pos > 0)
    {
      new_pos = cur_pos - 1;
      start_str_pos--;
    }
    break;
  case SB_THUMBTRACK:
    new_pos = HIWORD(wParam);
    k = new_pos - cur_pos;
    start_str_pos += k;
    break;
  }

  if (new_pos != cur_pos)
  {
    SetScrollPos(hwnd, SB_HORZ, new_pos, TRUE);
    InvalidateRect(hwnd, NULL, TRUE);
  }

} /* End of 'window::WMDestroy' function */


/* WM_DESTROY message processing */
void window::WMKeydown(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam)
{
  switch (wParam)
  {
  case VK_UP:
    SendMessage(hwnd, WM_VSCROLL, SB_LINEUP, 0);
    break;
  case VK_DOWN:
    SendMessage(hwnd, WM_VSCROLL, SB_LINEDOWN, 0);
    break;
  case VK_LEFT:
    SendMessage(hwnd, WM_HSCROLL, SB_LINELEFT, 0);
    break;
  case VK_RIGHT:
    SendMessage(hwnd, WM_HSCROLL, SB_LINERIGHT, 0);
    break;
  case VK_PRIOR:
    SendMessage(hwnd, WM_VSCROLL, SB_PAGEUP, 0);
    break;
  case VK_NEXT:
    SendMessage(hwnd, WM_VSCROLL, SB_PAGEDOWN, 0);
    break;
  }
} /* End of 'window::WMDestroy' function */


/* WM_DESTROY message processing */
void window::WMDestroy(HWND &hwnd, UINT &message, WPARAM &wParam, LPARAM &lParam)
{
  PostQuitMessage(0);
} /* End of 'window::WMDestroy' function */

/* END OF 'window.cpp' FILE */
