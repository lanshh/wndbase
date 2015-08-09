#ifndef _MESSAGEBOX_H_
#define _MESSAGEBOX_H_
#define SW_OK                       0x00000000L
#define SW_OKCANCEL                 0x00000001L
#define SW_ABORTRETRYIGNORE         0x00000002L
#define SW_YESNOCANCEL              0x00000003L
#define SW_YESNO                    0x00000004L
#define SW_RETRYCANCEL              0x00000005L
#define ID_YES                      1
#define ID_NO                       2
#define ID_CANCEL                   3
#define ID_OK                       4
DWORD SWNMessageBox(HWND ,TCHAR *,TCHAR *,DWORD );
#endif