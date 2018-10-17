#include "stdafx.h"
#include "InteractScreenCaptureDlg.h"
#include "../ModelDef.h"


CInteractScreenCaptureDlg::CInteractScreenCaptureDlg()
{
    m_rectSelect.left = -1;
    m_rectSelect.right = -1;
    m_rectSelect.top = -1;
    m_rectSelect.bottom = -1;
}

CInteractScreenCaptureDlg::~CInteractScreenCaptureDlg()
{

}

LRESULT CInteractScreenCaptureDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return 0;
}

void CInteractScreenCaptureDlg::OnClick(TNotifyUI& msg)
{
    CDuiString sCtrlName = msg.pSender->GetName();

    if (sCtrlName == _T("btn_ok")) {
        DoOk();
    }
    else if (sCtrlName == _T("btn_cancel") || sCtrlName == _T("closebtn")) {
        PostMessage(WM_CLOSE, IDCANCEL, 0);
    }
}

void CInteractScreenCaptureDlg::DoOk()
{
    CEditUI* edt_x = static_cast<CEditUI*>(FindControl(_T("edt_x")));
    CEditUI* edt_y = static_cast<CEditUI*>(FindControl(_T("edt_y")));
    CEditUI* edt_w = static_cast<CEditUI*>(FindControl(_T("edt_w")));
    CEditUI* edt_h = static_cast<CEditUI*>(FindControl(_T("edt_h")));

    if (edt_x && edt_y && edt_w && edt_h) {
        int x = _ttoi(edt_x->GetText());
        int y = _ttoi(edt_y->GetText());
        int w = _ttoi(edt_w->GetText());
        int h = _ttoi(edt_h->GetText());

        if ((x >= 0 && y >= 0 && w >= 0 && h >= 0) || (x == -1 && y == -1 && w == -1 && h == -1)) {
            m_rectSelect.left = x;
            m_rectSelect.right = x + w;
            m_rectSelect.top = y;
            m_rectSelect.bottom = y + h;

            PostMessage(WM_CLOSE, IDOK, NULL);
        }
        else {
            DuiMessageBox(GetHWND(), _T("请输入正确坐标"), INTERACT_TITLE, MB_OK);
        }
    }
}

RECT* CInteractScreenCaptureDlg::GetSelectRect()
{
    if (m_rectSelect.left == -1 && m_rectSelect.right == -1 && m_rectSelect.top == -1 && m_rectSelect.bottom == -1) {
        return NULL;
    }
    return &m_rectSelect;
}
