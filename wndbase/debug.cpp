#include "stdafx.h"
#include "debug.h"
			                         //"19:02:10   App start..."
#define logmsga "SNWTool log Message\r\nTime       Message\r\n----------------------------------------------------------------------------------------------\r\n"
void        debugInit       (TCHAR *debugpath);
static TCHAR debugfilename[260] = {0}; 

DWORD shWriteAsi(TCHAR * tFileName,BYTE * pbWriteBuf,DWORD dwBufLen,DWORD dwWritePoint,DWORD dwTryTime)
{
    HANDLE              hFile;
    DWORD               dwWantToWriteCnt;
    DWORD               dwHasWriteCnt;
    DWORD               dwWriteCnt;
    int                 iTryTime;
    iTryTime            = dwTryTime;
    hFile               = CreateFile(tFileName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    if (INVALID_HANDLE_VALUE == hFile) {
        return -1;
    }
    if ( ERROR_ALREADY_EXISTS  != GetLastError()) {
        dwWantToWriteCnt = strlen(logmsga);
        WriteFile(hFile,logmsga,dwWantToWriteCnt,&dwWriteCnt,NULL);
    }
    if (0xFFFFFFFF == dwWritePoint) {
        SetFilePointer(hFile,0,NULL,FILE_END);
    } else {
        SetFilePointer(hFile,dwWritePoint,NULL,FILE_BEGIN);
    }
    dwWantToWriteCnt    = dwBufLen;
    dwHasWriteCnt       = 0;
    do  {
        dwWriteCnt = 0;
        if (!WriteFile(hFile,pbWriteBuf + dwHasWriteCnt,dwWantToWriteCnt,&dwWriteCnt,NULL)) {
            CloseHandle(hFile);
            return -1;
        }
        dwWantToWriteCnt -= dwWriteCnt; 
        dwHasWriteCnt += dwWriteCnt;
    } while (dwWantToWriteCnt > 0);
    CloseHandle(hFile);
    return 0;
}

void debugInit(TCHAR *debugpath)
{
    TCHAR           *pos;
    SYSTEMTIME      LocalTime;
    GetLocalTime(&LocalTime);
    if(debugpath) { 
        wsprintf(debugfilename,TEXT("%s\\log"),debugpath);
        CreateDirectory(debugfilename,NULL);
        wsprintf(&debugfilename[_tcslen(debugfilename)],TEXT("\\snw_%d-%d-%d.log"),
        LocalTime.wYear,
		LocalTime.wMonth,
		LocalTime.wDay);
    } else {
        GetModuleFileName(NULL, debugfilename, 260);
        pos     = _tcsrchr(debugfilename, _T('\\'));
        wsprintf(&pos[1],TEXT("\\log"));
        CreateDirectory(debugfilename,NULL);
        wsprintf(&pos[_tcslen(pos)],TEXT("\\snw_%d-%d-%d.log"),
        LocalTime.wYear,
		LocalTime.wMonth,
		LocalTime.wDay);
    }
}

VOID _cdecl PrintMSGAA(const char *format,...)
{
    char            buffer[1024];
    va_list         args;
    SYSTEMTIME      LocalTime;
    INT             iLength     = 0;
    GetLocalTime( &LocalTime );
    iLength = sprintf( buffer, "%02d:%02d:%02d   ", LocalTime.wHour, LocalTime.wMinute, LocalTime.wSecond );
    va_start(args, format);
    iLength += vsprintf(&buffer[iLength], format, args);
    va_end(args);
    buffer[iLength]      = '\0';
    if(TEXT('\0') == debugfilename[0] ){
        debugInit(NULL);
    }
    OutputDebugStringA(buffer);
    shWriteAsi(debugfilename,(BYTE *)buffer,strlen(buffer)*sizeof(buffer[0]),0xFFFFFFFF,0);
}
VOID _cdecl PrintMSGWA(const TCHAR *format,...)
{
    va_list         args;
    TCHAR           szShowStr[1024];
    char            *szStr;
    SYSTEMTIME      LocalTime;
    INT             iLength;
    UINT            iLen;
    GetLocalTime( &LocalTime );
    iLength = wsprintf(szShowStr, TEXT("%02d:%02d:%02d   "), LocalTime.wHour, LocalTime.wMinute, LocalTime.wSecond );
    va_start(args, format);
    iLength += wvsprintf(&szShowStr[iLength], format, args);
    va_end(args);
    szShowStr[iLength] = TEXT('\0');
    if(TEXT('\0') == debugfilename[0] ){
        debugInit(NULL);
    }
    iLen = WideCharToMultiByte(CP_ACP, 0,
                                    szShowStr, -1,
                                    NULL, 0, NULL, NULL) + 1;
    szStr = (LPSTR)LocalAlloc(LPTR,iLen);
    if (szStr) {
        WideCharToMultiByte(CP_ACP, 0,
                            szShowStr, -1,
                            szStr, iLen,
                            NULL, NULL);
        OutputDebugStringA(szStr);
        shWriteAsi(debugfilename,(BYTE *)szStr,strlen(szStr)*sizeof(szStr[0]),0xFFFFFFFF,0);
        LocalFree(szStr);
    }
}
class CDebug
{
    typedef enum {
        DEBUG_ALL       = -1,        /* Debug level. Allows debug, info, warning and error traces */
        DEBUG_INFO      = 0,         /* information level. Default severity . Allows info, warning and error traces*/
        DEBUG_WARNING   = 1,         /* warning level. Allows warning and error traces*/
        DEBUG_ERROR     = 2,         /* error level. Allows only error traces*/
        DEBUG_OFF      = 3          /* none level. No traces. Default when ipicom starts*/
    } DEBUG_LEVEL;
private:
    TCHAR name[260];
    TCHAR path[260];
public:
    void DebugInit();
    void SetDebugPath(char *);
    void SetDebugPath(TCHAR *);
    void SetDebugName(char *);
    void SetDebugName(TCHAR *);
    void _cdecl PrintMSGW(DEBUG_LEVEL dlLevel,const TCHAR *format,...);
    void _cdecl PrintMSGA(const CHAR *format,...);
};
