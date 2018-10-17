#include "stdafx.h"
#include "InteractWndSelectDlg.h"
#include "../ModelDef.h"
#include <Psapi.h>


CInteractWndSelectDlg::CInteractWndSelectDlg()
{
    m_nSelectWinIndex = -1;
}

CInteractWndSelectDlg::~CInteractWndSelectDlg()
{

}

LRESULT CInteractWndSelectDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    UpdateWindowList();

    CVerticalLayoutUI * pLayout = (CVerticalLayoutUI*)FindControl(_T("list_wnd"));
    if (pLayout) {
        for (int i = 0; i < (int)m_vectWindowInfo.size(); i++) {
            COptionUI * pOption = new COptionUI();
            pLayout->Add(pOption);

            pOption->SetText(m_vectWindowInfo[i].info.c_str());
            pOption->SetTag(i);
            pOption->SetName(_T("win"));
            pOption->SetGroup(_T("wnd_group"));
            pOption->SetAttribute(_T("selectedimage"), _T("file='checkbox.png' dest='0,0,14,14' source='56,0,70,14'"));
            pOption->SetAttribute(_T("normalimage"), _T("file='checkbox.png' dest='0,0,14,14' source='0,0,14,14'"));
            pOption->SetAttribute(_T("textpadding"), _T("16,0,0,0"));
            pOption->SetAttribute(_T("padding"), _T("2,2,2,2"));
            pOption->SetAttribute(_T("align"), _T("left"));
            pOption->SetAttribute(_T("height"), _T("14"));
        }
    }

    return 0;
}

void CInteractWndSelectDlg::OnClick(TNotifyUI& msg)
{
    CDuiString sCtrlName = msg.pSender->GetName();

    if (sCtrlName == _T("btn_ok"))
    {
        if (m_nSelectWinIndex != -1) {
            PostMessage(WM_CLOSE, IDOK, NULL);
        }
    }
    else if (sCtrlName == _T("btn_cancel") || sCtrlName == _T("closebtn"))
    {
        PostMessage(WM_CLOSE, IDCANCEL, 0);
    }
    else if (sCtrlName == _T("win"))
    {
        m_nSelectWinIndex = msg.pSender->GetTag();
    }
}

void CInteractWndSelectDlg::UpdateWindowList()
{
    HWND window = FindWindowEx(GetDesktopWindow(), NULL, NULL, NULL);

    while (true) {
        window = GetNextWindow(window, GW_HWNDNEXT);
        if (window == NULL) {
            break;
        }

        if (!IsWindowVisible(window) || IsIconic(window)) {
            continue;
        }

        DWORD styles = (DWORD)GetWindowLongPtr(window, GWL_STYLE);
        DWORD ex_styles = (DWORD)GetWindowLongPtr(window, GWL_EXSTYLE);

        if (ex_styles & WS_EX_TOOLWINDOW) {
            continue;
        }
        if (styles & WS_CHILD) {
            continue;
        }
        DWORD progressId = -1;
        GetWindowThreadProcessId(window, &progressId);
        if (progressId == GetCurrentProcessId()) {
            continue;
        }

        HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, progressId);
        if (!process) {
            continue;
        }

        TCHAR path[MAX_PATH];
        if (!GetProcessImageFileName(process, path, MAX_PATH)) {
            continue;
        }
        tstring exe_name = path;
        exe_name = exe_name.substr(exe_name.rfind(_T("\\")) + 1);

        TCHAR title[MAX_PATH];
        GetWindowText(window, title, MAX_PATH);

        WindowInfo info;
        info.hwnd = window;
        info.info = _T("[");
        info.info.append(exe_name);
        info.info.append(_T("]:"));
        info.info.append(title);

        m_vectWindowInfo.push_back(info);
    }


}

HWND CInteractWndSelectDlg::GetSeletcWnd()
{
    if (m_nSelectWinIndex >= 0 && m_nSelectWinIndex < (int)m_vectWindowInfo.size()) {
        return m_vectWindowInfo[m_nSelectWinIndex].hwnd;
    }
    return NULL;
}
