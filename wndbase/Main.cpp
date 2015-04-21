/*******************************************************************************
*filename     :main.c
*synopsis     :appliction starts here
*created      :lanshh 2015-01-30
*******************************************************************************/
#include "stdafx.h"
#include "utils.h"
#include "WndMain.h"
/*******************************************************************************
*Fun Name: int InitInstance(HINSTANCE hInstance)
*Desc    : Get and save some system parameters such as : 
*          screen Height and Width  save hinstance 
*
*******************************************************************************/
int InitInstance(HINSTANCE hInstance)
{
    HWND                    hWnd;
#ifdef COMMCTL
    INITCOMMONCONTROLSEX    LpInitCtrls;
    LpInitCtrls.dwSize      = sizeof(INITCOMMONCONTROLSEX);
    LpInitCtrls.dwICC       = ICC_LISTVIEW_CLASSES|ICC_UPDOWN_CLASS;
    InitCommonControlsEx(&LpInitCtrls);
#endif
    hWnd                    = NULL;
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
    hWnd = FindWindow (szAppName, NULL);
    if (hWnd) 
    {
        SetForegroundWindow ((HWND)(((DWORD)hWnd) | 0x01));    
        return -1;
    }
#endif
    return 0;
}
#ifdef _WIN32_WCE 
int WINAPI WinMain(     HINSTANCE   hInstance,
                        HINSTANCE   hPrevInstance,
                        LPTSTR      lpCmdLine,
                        int         nCmdShow)
#else
int APIENTRY _tWinMain(HINSTANCE    hInstance,
                        HINSTANCE   hPrevInstance,
                        LPTSTR      lpCmdLine,
                        int         nCmdShow)

#endif //#ifdef _WIN32_WCE
{
    HWND    hWndMain;
    MSG     msg;
    if (!InitAppInfo(hInstance)) {
        return 0;
    }
    if (0 != InitInstance (hInstance))
    {
        return 0;
    }
    hWndMain = CreateWndMain(hInstance,nCmdShow);
    if( NULL == hWndMain){
        return 0;
    }
    /*
    *Message loop
    */
    while (GetMessage(&msg, NULL, 0, 0)) {
#if USE_TA
    if (!TranslateAccelerator( ghwndMain, ghAccel, &msg ))
#else 
#endif
        {
            TranslateMessage( &msg ) ;
            DispatchMessage( &msg ) ;
        }
    }
    DeInitAppInfo();
    return (int) msg.wParam;	
}
