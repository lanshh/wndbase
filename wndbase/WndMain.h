/*******************************************************************************
*filename     :WndMain.h
*synopsis     :this file contains codes create a the main window
*created      :lanshh 2015-01-30
*******************************************************************************/
LRESULT CALLBACK WndMainProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
HWND    CreateWndMain       (HINSTANCE hInstance, int nCmdShow);
LRESULT WndMainCmdProc      (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam);
LRESULT WndMainCreateProc   (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam);
LRESULT WndMainCloseProc    (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam);
LRESULT WndMainDestroyProc  (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam);
LRESULT about               (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam);
LRESULT WndMainPaint        (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam);
LRESULT WndMainEeaseProc    (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam);
LRESULT WndMainSize         (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam);


