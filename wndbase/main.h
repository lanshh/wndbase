#ifndef _MAIN_H_
#define _MAIN_H_
inline VOID logMsgs(HWND hWnd)
{
    int     iRet;
    TCHAR   szMsg[256];
    iRet    = GetLastError();
    wsprintf(szMsg,TEXT("GetLastError():%d"),iRet);
    MessageBox(hWnd,szMsg,TEXT("Error"),NULL);
}

#endif