#include "stdafx.h"
#include "utils.h"
#include "resource.h"
#include "XmlTreeDlg.h"
HWND        g_hXmlDlg       = NULL;
//HTREEITEM   ghTreeRoot      = NULL;

static const DlgMessageMap XmlDlgMsgs[] = 
{
    WM_INITDIALOG       ,XmlDlgInitDlg,
    WM_COMMAND          ,XmlDlgCmdProc,
    WM_DESTROY          ,XmlDlgDestroyProc,
    //WM_SIZE             ,XmlDlgSize,
};
                             
static const DlgMessageCmdMap XmlDlgCmdMsgs[] = 
{
    0,0
};
INT_PTR XmlDlgCmdProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
    INT i;							   			
    for (i = 0; i < dim(XmlDlgCmdMsgs); i++)
    {						  
        if (LOWORD (wParam) == XmlDlgCmdMsgs[i].Code)	
        {
            return (*XmlDlgCmdMsgs[i].Fxn)(hWnd, wParam, lParam);
        }	
    }				  
    return FALSE;
}
INT_PTR XmlDlgOpen(HWND hWnd)
{
    return DialogBoxParam(gethResInstance(), MAKEINTRESOURCE(IDD_DLG_XMLTREE), hWnd,(DLGPROC)XmlDlgProc,0);
}
HWND XmlDlgCreate(HWND hWnd)
{
    return CreateDialog(gethResInstance(), MAKEINTRESOURCE(IDD_DLG_XMLTREE), hWnd,(DLGPROC)XmlDlgProc);
}
INT_PTR  XmlDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{

    INT     i;							   
    for (i = 0; i < dim(XmlDlgMsgs); i++)
    {						  
        if (wMsg == XmlDlgMsgs[i].Code)
        {
            return (*XmlDlgMsgs[i].Fxn)(hWnd, wMsg, wParam, lParam);
        }			
    }	
    return FALSE;
}
INT_PTR XmlDlgInitDlg(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
    g_hXmlDlg = hWnd;

    return FALSE;
}
INT_PTR XmlDlgDestroyProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}
BOOL XmlDlgDestroy(VOID)
{
    if ( NULL != g_hXmlDlg ){
        DestroyWindow(g_hXmlDlg);
        g_hXmlDlg   = NULL;
    }
    return TRUE;
}


