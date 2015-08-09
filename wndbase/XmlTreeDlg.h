#ifndef _XMLTREEDLG_H_
#define _XMLTREEDLG_H_
INT_PTR     XmlDlgOpen          (HWND hWnd);
HWND        XmlDlgCreate        (HWND hWnd);
BOOL        XmlDlgDestroy       (VOID);
INT_PTR     XmlDlgInitDlg       (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
INT_PTR     XmlDlgProc          (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
INT_PTR     XmlDlgCmdProc       (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
INT_PTR     XmlDlgInitDlg       (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
INT_PTR     XmlDlgDestroyProc   (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
INT_PTR     XmlDlgLbdProc       (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
INT_PTR     XmlDlgFocusProc     (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
#endif