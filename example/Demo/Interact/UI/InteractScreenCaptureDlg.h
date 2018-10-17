#ifndef _INTERACT_SCREEN_CAPTURE_H_
#define _INTERACT_SCREEN_CAPTURE_H_

#pragma once

#include "../../UI/UI.h"

class CInteractScreenCaptureDlg : public CDuiDialogImpl < CInteractScreenCaptureDlg >
{
public:
    CInteractScreenCaptureDlg();
    virtual ~CInteractScreenCaptureDlg();

public:
    DUI_DECLARE_SKIN_FILE(_T("InteractScreenCaptureDlg.xml"));

    DUI_WIN_BEGIN_MSG_MAP(CInteractScreenCaptureDlg, CDuiDialogImpl<CInteractScreenCaptureDlg>)
        DUI_WIN_MESSAGE_HANDLER(WM_CREATE, OnCreate)
        DUI_WIN_END_MSG_MAP()

        LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
    RECT* GetSelectRect();

public:
    virtual void OnClick(TNotifyUI& msg);

private:
    void DoOk();
private:
    RECT m_rectSelect;
};

#endif