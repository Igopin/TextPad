/* Main WinGDI header file */

#ifndef _WINGDI_H_
#define _WINGDI_H_

#include "defines.h"

/* This function is called by the Windows function DispatchMessage() */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif /* _WINGDI_H_ */


/* END OF 'wingdi.h' FILE */
