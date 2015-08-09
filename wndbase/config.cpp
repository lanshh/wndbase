/*******************************************************************************
*FileName       :config.c
*Description    :All global configs variables and api 
*Created        :lanshh 2015-03-02
*last modified  :lanshh 2015-04-21 
*******************************************************************************/
#include "stdafx.h"
#include "utils.h"
//PSMODE
static APPINFO gAppInfo;
DWORD InitAppInfo(HINSTANCE  hInst)
{
    RECT    rcArea; 
    DWORD   dwRet     = 0;
    TCHAR   szFilePath[MAX_PATH + 1];
    memset(szFilePath,0,sizeof(szFilePath));
    memset(&gAppInfo,0,sizeof(APPINFO));
    gAppInfo.hInst = hInst;
    GetSysTimeDataSecW(gAppInfo.Date,dim(gAppInfo.Date));
    memset(gAppInfo.exePath,0,sizeof(gAppInfo.exePath));
    if (!GetVersionEx(&gAppInfo.OSVer)) {
        gAppInfo.OSVer.dwBuildNumber = 0;
    }
    if( GetModuleFileName(gAppInfo.hInst, szFilePath, MAX_PATH)){
        (_tcsrchr(szFilePath, _T('\\')))[1] = 0;
        _tcscpy_s(gAppInfo.exePath,MAX_PATH,szFilePath);
    } else {
        _tcscpy_s(gAppInfo.exePath,MAX_PATH,TEXT("C:\\"));
    }
    wsprintf(gAppInfo.gdbgdir,TEXT("%slog\\"),gAppInfo.exePath );
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rcArea, 0);
    gAppInfo.iSysWidth     =  rcArea.right  - rcArea.left;
    gAppInfo.iSysHeight    =  rcArea.bottom - rcArea.top;
    dwRet     = 1;
//InitAppInfoErr:
    if( !dwRet) {
        DeInitAppInfo();
    }
    LDEGMSG(DEBUG_LOG,("InitAppInfo exit %d\r\n",dwRet));
    return dwRet;
}
VOID DeInitAppInfo(VOID)
{
    LDEGMSG(DEBUG_LOG,("DeInitAppInfo exit\r\n"));
    return ;
}
APPINFO * SetAppInfo(VOID)
{
    return &gAppInfo;
}
const APPINFO *GetAppInfo(VOID)
{
    return &gAppInfo;
}
HINSTANCE gethInstance()
{
    return gAppInfo.hInst;
}
HINSTANCE gethResInstance()
{
    if(NULL != gAppInfo.hResourceInst){
        return gAppInfo.hResourceInst;
    } else {
        return gAppInfo.hInst;
    }
}
/*******************************************************************************
*Fun Name: BOOL getOSVersion(OSVERSIONINFO * osv)
*Desc    : 
*
*******************************************************************************/
BOOL GetOsVersion(OSVERSIONINFO * osv)
{
    osv->dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx(osv))
        return FALSE;
    return TRUE ;
}