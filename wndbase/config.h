/*******************************************************************************
*FileName       :config.h
*Description    :All global configs variables and api 
*Created        :lanshh 2015-03-02
*last modified  :lanshh 2015-04-21 
*******************************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_
/************************************************************************/
/* Global Variable Define                                               */
/************************************************************************/
#if 0

/****************** Global Variabal Define In Main.cpp ****************************/
extern OSVERSIONINFO g_OSV;         // os version
extern HINSTANCE     g_hInst;       //Global Variable Instance Handle
extern int           g_iSysWidth;   //Global Variable Screen Width
extern int           g_iSysHeight;  //Global Variable Screen Height

/****************** Global Variabal Define In WndMain.cpp ****************************/
extern HWND          g_hWndMain;    //The Main Window Handle 
#ifdef STATUSBAR
extern HWND          g_hWndStatusBar;
#endif

#ifdef COMMANDBAR
extern HWND          g_hWndCommandBar;
extern int           g_CommandBarHeight;
#else
extern int           g_CommandBarHeight;
#endif

#endif

#define STATUSBAR
//#define COMMANDBAR
#define COMMCTL
#define USE_MENU        1
#define WNDBASE_TOPMOST 0

#ifdef _WIN32_WCE
#define WINWIDTH       g_wSysWidth  //400     
#define WINHEIGHT      g_wSysHeight //300
#else
#define WINWIDTH       800     
#define WINHEIGHT      600
#endif
/********************Message Map Struct ****************************/
typedef struct _MessageMap_
{
	UINT Code;                                 
	LRESULT (*Fxn)(HWND, UINT, WPARAM, LPARAM);
}MessageMap,*pMessageMap;
typedef struct _MessageCmdMap_
{
	UINT Code;                                 
	LRESULT (*Fxn)(HWND, WPARAM, LPARAM);
}MessageCmdMap,*pMessageCmdMap;
typedef struct _DlgMessageMap_
{
	UINT Code;                                 
	INT_PTR (*Fxn)(HWND, UINT, WPARAM, LPARAM);
}DlgMessageMap,*pDlgMessageMap;
typedef struct _DlgMessageCmdMap_
{
	UINT Code;                                 
	INT_PTR (*Fxn)(HWND, WPARAM, LPARAM);
}DlgMessageCmdMap,*pDlgMessageCmdMap;

typedef struct _APP_CFG_
{
    int             i;
    unsigned short  CRC;
}APPCFG,*pAPPCFG;

typedef struct _APP_INFO_
{   
    HINSTANCE       hInst;
    APPCFG          appCfg;
    LONG            lock;
    LONG            lRefCount;
    OSVERSIONINFO   OSVer;
    INT             iSysWidth;    // screen width
    INT             iSysHeight;   // screen height
    TCHAR           exePath[MAX_PATH];
    TCHAR           gdbgdir[MAX_PATH];
    HFONT           hFont;
    TCHAR           Date[32];
    HINSTANCE       hResourceInst;
    HWND            hWndMain;
    HWND            hXmlDlg;
}APPINFO,*pAPPINFO;
DWORD           InitAppInfo     (HINSTANCE  hInst);
VOID            DeInitAppInfo   (VOID);
APPINFO         *SetAppInfo     (VOID);
const APPINFO   *GetAppInfo     (VOID);
HINSTANCE       gethInstance    (VOID);
HINSTANCE       gethResInstance (VOID);
BOOL            GetOsVersion    (OSVERSIONINFO * osv);
#endif
