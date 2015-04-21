/******************************************************************************
*filename     :WndMain.cpp
*synopsis     :this file contains codes create a the main window
*created      :lanshh 2015-01-30
*last modified:
******************************************************************************/
#include "stdafx.h"
#include "utils.h"
#include "resource.h"
#include "XmlTreeDlg.h"
#include "WndMain.h"
#include "MessageBox.h"
#ifdef RESOURCE 
TCHAR szWndMainTitle[MAX_LOADSTRING];   // The Title Of  WndBase
TCHAR szWndMainClass[MAX_LOADSTRING];   // The Main Window Class Name
#else
TCHAR *szWndMainTitle = _T("wndbase");       //the main window name
TCHAR *szWndMainClass = _T("wndbaseClass");
#endif
static HWND ghXmlDlg  = NULL;
const MessageMap WndMainMsgs[] = 
{
    WM_CLOSE        ,WndMainCloseProc,
    WM_DESTROY      ,WndMainDestroyProc,
    WM_CREATE       ,WndMainCreateProc,
    WM_COMMAND      ,WndMainCmdProc,
    WM_SIZE         ,WndMainSize
    //WM_PAINT        ,WndMainPaint,
    //WM_ERASEBKGND   ,WndMainEeaseProc
};
const MessageMap WndMainCmdMsgs[] = 
{
    0,0
};
HWND CreateWndMain(HINSTANCE hInstance, int nCmdShow)
{
    APPINFO             *AppInfo    = SetAppInfo();
    HWND                hWndMain;
    WNDCLASS            wc;
    ATOM                awCls;
#ifdef RESOURCE 
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_GDIBITMAPSCALING, szWindowClass, MAX_LOADSTRING);
#endif
    wc.style                = CS_HREDRAW | CS_VREDRAW;      // Window style
    wc.lpfnWndProc          = WndMainProc;                  // Callback function
    wc.cbClsExtra           = 0;                            // Extra class data
    wc.cbWndExtra           = 0;                            // Extra window data
    wc.hInstance            = hInstance;                    // Owner handle
    wc.hIcon                = NULL;                         // Application icon
    wc.hCursor              = LoadCursor (NULL, IDC_ARROW); // Default cursor
    wc.hbrBackground        = (HBRUSH)COLOR_WINDOW;
#if USE_MENU
    wc.lpszMenuName         = MAKEINTRESOURCE(NULL);// Menu name
#else 
    wc.lpszMenuName         = NULL;                        // Menu name
#endif
    wc.lpszClassName        = szWndMainClass;               // Window class name
    awCls                   = RegisterClass (&wc);
    if ( 0== awCls) {
        return NULL;
    }

    hWndMain = CreateWindowEx(NULL,
                MAKEINTRESOURCE(awCls),
		        szWndMainTitle,
#ifndef _WIN32_WCE
                WS_CAPTION|WS_SYSMENU|WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SIZEBOX,
#else
                WS_CAPTION|WS_SYSMENU|WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SIZEBOX,
#endif
                (AppInfo->iSysWidth -  WINWIDTH)/2,     //central show window
                (AppInfo->iSysHeight - WINHEIGHT)/2,
                WINWIDTH ,
                WINHEIGHT ,
		        NULL, 
		        NULL, 
		        hInstance, 
		        NULL);
    if ( FALSE == IsWindow(hWndMain) )
    {
        return NULL;
    }
    AppInfo->hWndMain = hWndMain;
#if WNDBASE_TOPMOST
    SetWindowPos(g_hWndMain,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
#endif
    ShowWindow(hWndMain, nCmdShow);
    UpdateWindow(hWndMain);
    return hWndMain;
}
LRESULT CALLBACK WndMainProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
    INT i;							   
    for (i = 0; i < dim(WndMainMsgs); i++) 
    {						  
        if (wMsg == WndMainMsgs[i].Code)	
        {
            return (*WndMainMsgs[i].Fxn)(hWnd, wMsg, wParam, lParam);
        }			
    }	
    return DefWindowProc (hWnd, wMsg, wParam, lParam);
}
LRESULT WndMainCmdProc(HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam)
{
    INT i;							   			
    for (i = 0; i < dim(WndMainCmdMsgs); i++) 
    {						  
        if (LOWORD (wParam) == WndMainCmdMsgs[i].Code)	
        {
            return (*WndMainCmdMsgs[i].Fxn)(hWnd, wMsg, wParam, lParam);
        }	
    }				  
    return DefWindowProc (hWnd, wMsg, wParam, lParam);
}
LRESULT WndMainCreateProc (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam)
{
    //APPINFO *AppInfo = SetAppInfo();
    //HWND    hWndTemp;
    //int     ix,iy;
    //SendMessage(hWnd, WM_SETICON, (WPARAM)TRUE, (LPARAM)LoadIcon(gethInstance(), (LPCTSTR)IDI_ICON1));
    ghXmlDlg         = XmlDlgCreate(hWnd);
	return 0;
}
LRESULT WndMainCloseProc (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam)
{
    int iRet;
    iRet = SWNMessageBox(hWnd,_T("确定要关闭窗口吗？"),_T("提示"),SW_OKCANCEL);
    if (ID_OK == iRet)
    {
        DestroyWindow(hWnd);
    }
    return 0;
}
LRESULT WndMainPaint (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam)
{
    PAINTSTRUCT     ps;
    HDC             hdc;
    hdc = BeginPaint (hWnd, &ps);
    //_CrtDbgReport(0, NULL, 0, NULL, "%d\r\n", ps.fErase);
    EndPaint (hWnd, &ps) ;
    return 1;
}
LRESULT WndMainEeaseProc (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam)
{
    return 1;
}

LRESULT WndMainDestroyProc(HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam)
{
    //we need detroy all the controls created by ourself
    if (NULL != ghXmlDlg){
        XmlDlgDestroy();
        ghXmlDlg = NULL;
    }
    PostQuitMessage(0);
    return 0;
}
LRESULT about(HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam)
{
    return 0;
}

LRESULT WndMainSize(HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam)
{
    WORD                   nWidth;
    WORD                   nHeight;
    //RECT                   rt;
    nWidth                 = LOWORD(lParam); 
    nHeight                = HIWORD(lParam);
    if(NULL != ghXmlDlg) {
        MoveWindow(ghXmlDlg,0,0,nWidth, nHeight, TRUE);
    }
    return TRUE;
}