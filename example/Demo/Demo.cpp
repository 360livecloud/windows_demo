// demo.cpp : main source file for demo.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>

#include "resource.h"

#include "Common/Crash.h"
#include "UI/MainWnd.h"
#include "Interact/UI/InteractMainDlg.h"

CAppModule _Module;

int Run(HINSTANCE hInstance, LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
    CCrash::Init();

    CLog::GetInstance().SetEnable(true);
    CLog::GetInstance().SetLogLevel(LOG_LEVEL_TRACE);

    CPaintManagerUI::SetInstance(hInstance);

    CInteractMainDlg mainWnd;
    mainWnd.Create(NULL, _T("360 ”∆µ‘∆"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 800, 572);
    mainWnd.CenterWindow();
    mainWnd.ShowWindow();

    CPaintManagerUI::MessageLoop();

	return 0;
}
void ShowMyWindow(HWND hwnd)
{
    if (hwnd == NULL || !::IsWindow(hwnd)) {
        return;
    }
    if (::IsIconic(hwnd))
        ::ShowWindow(hwnd, SW_RESTORE);
    ::SetForegroundWindow(hwnd);
    ::UpdateWindow(hwnd);
    ::InvalidateRect(hwnd, NULL, TRUE);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));


    HANDLE hOneInstMutex = CreateMutex(NULL, TRUE, TEXT("LiveDemoMutex"));
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        HWND hwndInteract = FindWindow(_T("InteractAnchorDlg"), NULL);
        if (hwndInteract && IsWindowVisible(hwndInteract)) {
            ShowMyWindow(hwndInteract);
        }
        else {
            HWND hwndMain = FindWindow(_T("InteractMainDlg"), NULL);
            if (hwndMain && IsWindowVisible(hwndMain)) {
                ShowMyWindow(hwndMain);
            }
        }

        CloseHandle(hOneInstMutex);
        return false;
    }

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

    int nRet = Run(hInstance, lpstrCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

    CloseHandle(hOneInstMutex);

	return nRet;
}
