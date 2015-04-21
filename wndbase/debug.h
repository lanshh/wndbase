#ifndef _DEBUG_H_
#define _DEBUG_H_
int  _cdecl printLog        (const char* pFormat,...);
void _cdecl printLogW       (const char* pFormat,...);
void _cdecl PrintMSG        (const TCHAR *format,...);
void _cdecl PrintMSGAA      (const char *format,...);
void _cdecl PrintMSGWA      (const TCHAR *format,...);
#define LSHH_DEBUG
#if defined(LSHH_DEBUG)
    #define     DEBUG_WARN      TRUE
    #define     DEBUG_ERR       TRUE
    #define     DEBUG_LOG       TRUE
    #define     DEBUG_NONE      FALSE
    #define     DEBUG_CONFIG    FALSE
    #define     LDEGMSG(cond,printf_exp)            ((cond)?(PrintMSGAA printf_exp),1:0)
    #define     LDEGMSGW(cond,printf_exp)            ((cond)?(PrintMSGWA printf_exp),1:0)
#else 
    #define     DEBUG_ERR       FALSE
    #define     DEBUG_LOG       FALSE
    #define     DEBUG_WARN      FALSE
    #define     DEBUG_CONFIG    FALSE
    #define     DEBUG_NONE      FALSE
    #define     LDEGMSG(cond,printf_exp)
    #define     LDEGMSGW(cond,printf_exp)
#endif

#endif
