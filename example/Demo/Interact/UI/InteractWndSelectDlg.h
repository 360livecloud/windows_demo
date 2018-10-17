#ifndef _INTERACT_WND_SELECT_H_
#define _INTERACT_WND_SELECT_H_

#pragma once

#include "../../UI/UI.h"

typedef struct WindowInfo
{
    tstring info;
    HWND hwnd;

    WindowInfo()
    {
        hwnd = NULL;
    }
} WindowInfo;

class CInteractWndSelectDlg : public CDuiDialogImpl < CInteractWndSelectDlg >
{
public:
    CInteractWndSelectDlg();
    virtual ~CInteractWndSelectDlg();

public:
    DUI_DECLARE_SKIN_FILE(_T("InteractWndSelectDlg.xml"));

    DUI_WIN_BEGIN_MSG_MAP(CInteractWndSelectDlg, CDuiDialogImpl<CInteractWndSelectDlg>)
        DUI_WIN_MESSAGE_HANDLER(WM_CREATE, OnCreate)
        DUI_WIN_END_MSG_MAP()

        LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
    virtual void OnClick(TNotifyUI& msg);
    HWND GetSeletcWnd();


private:
    void UpdateWindowList();
private:

    std::vector<WindowInfo> m_vectWindowInfo;

    int m_nSelectWinIndex;
};

#endif