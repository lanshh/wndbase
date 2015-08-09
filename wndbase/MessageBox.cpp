#include "stdafx.h"
#include "utils.h"
#include "resource.h"
#include "MessageBox.h"
static TCHAR *g_szMsg         = NULL;
static TCHAR *g_szTitle       = NULL;
static DWORD g_dwFlag           = 0;
BOOL CALLBACK MessageBoxProc( HWND, UINT, WPARAM, LPARAM );
DWORD SWNMessageBox(HWND hWnd,TCHAR *szMsg,TCHAR *szTitle,DWORD flag)
{
    g_szMsg     = szMsg;
    if(szTitle) {
        g_szTitle   = szTitle;
    } else {
        g_szTitle = TEXT("Note");
    }
    if(szMsg) {
        g_szMsg = szMsg;
    } else {
        g_szMsg = TEXT("");
    }
    g_dwFlag    = flag;
    return DialogBox(gethResInstance(), MAKEINTRESOURCE(DLG_SELECT), hWnd, MessageBoxProc);
}
UINT InitMessageBox(HWND hDlg)
{
    return 0;
}
BOOL CALLBACK MessageBoxProc(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    int             i,j;
    RECT            rect;
    WORD            nWidth;
    WORD            nHeight;
    TCHAR           szMsg[128];
    TCHAR           szTitle[32];
    switch(uMessage)
    {
        case WM_INITDIALOG:{
            SetDlgItemText(hdlg,IDC_ST_SHOW,g_szMsg);
            SetWindowText(hdlg,g_szTitle);
            //LoadString(gethResInstance(),IDS_OK,szTitle,32);
            //SetDlgItemText(hdlg,IDOK,szTitle);
            //SetDlgItemText(hdlg,IDC_OK,szTitle);
            //LoadString(gethResInstance(),IDS_CANCEL,szTitle,32);
            //SetDlgItemText(hdlg,IDCANCEL,szTitle);
            if(SW_OK == g_dwFlag ){
                ShowWindow(GetDlgItem(hdlg,IDC_OK),SW_SHOW);
                ShowWindow(GetDlgItem(hdlg,IDCANCEL),SW_HIDE);
                ShowWindow(GetDlgItem(hdlg,IDOK),SW_HIDE);
            } else {
                ShowWindow(GetDlgItem(hdlg,IDC_OK),SW_HIDE);
                ShowWindow(GetDlgItem(hdlg,IDCANCEL),SW_SHOW);
                ShowWindow(GetDlgItem(hdlg,IDOK),SW_SHOW);
            }
            break;
        }
        case WM_TIMER:{
            break;
        }
        case WM_SIZE:{
            nWidth          = LOWORD(lparam); 
            nHeight         = HIWORD(lparam);

            break;
        }
        case WM_SYSKEYDOWN:
            if ( VK_ESCAPE == wparam ){
                EndDialog(hdlg, ID_CANCEL);
            } else if ( VK_RETURN == wparam ) {
                EndDialog(hdlg, ID_OK);
            }
            break;
        case WM_COMMAND:{
            switch(LOWORD(wparam)){
                //case ID_EXIT_ESCAP:
                case IDCANCEL:
                     EndDialog(hdlg, ID_CANCEL);
                    break;
                case IDC_OK:
                case IDOK:
                    EndDialog(hdlg, ID_OK);
                    break;
            }
            break;
        }
        case WM_SHOWWINDOW:{
            if (wparam == TRUE) {
                /* Position the property page centered over the parent. */
                GetWindowRect(hdlg, &rect);
                i = rect.right  - rect.left;
                j = rect.bottom - rect.top;
                GetWindowRect(GetParent(hdlg), &rect);
                if ((rect.right - rect.left) > i) {
                    i = rect.right - rect.left - i;
                } else {
                    i = 16;
                }
                if ((rect.bottom - rect.top) >  j) {
                     j = rect.bottom - rect.top -  j;
                } else {
                     j = 16;
                }
                SetWindowPos(hdlg, 0, rect.left + (i/2), rect.top +  (j/2), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            }
            break;
        case WM_DESTROY:
            break;
        }
    }
    return FALSE;
}

