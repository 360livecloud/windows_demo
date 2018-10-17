#include "stdafx.h"
#include "InteractTestDlg.h"
#include "../InteractGlobalManager.h"
#include "../DebugSetting.h"
#include "Control/VideoWnd.h"
#include <io.h>

#define SOUNDID1 100
#define SOUNDID2 101

DUI_BEGIN_MESSAGE_MAP(CInteractTestDlg, CDuiDialogImpl<CInteractTestDlg>)
DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
DUI_END_MESSAGE_MAP()



CInteractTestDlg::CInteractTestDlg()
{
    m_bAllVideoMute = false;
    m_bAllAudioMute = false;
    m_bAudioVolumeIndication = false;
    m_bDualStreamMode = false;
    m_bRomoteStreamLow = false;
    m_bEnableAudio = false;
    m_bEnableVideo = true;

    m_bEffect1Loaded = false;
    m_bEffect2Loaded = false;

    m_nEffectVolume = 100;
    m_nEffect1Volume = 100;
}

CInteractTestDlg::~CInteractTestDlg()
{
}

LRESULT CInteractTestDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    char path[512] = { 0 };
    GetModuleFileNameA(NULL, path, 511);
    std::string module_path = path;
    m_strEffectPath1 = module_path.substr(0, module_path.rfind("\\") + 1);
    m_strEffectPath1.append("effect1.wav");

    m_strEffectPath2 = module_path.substr(0, module_path.rfind("\\") + 1);
    m_strEffectPath2.append("effect2.wav");

    return 0;
}

LRESULT CInteractTestDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return 0;
}

void CInteractTestDlg::OnClick(TNotifyUI& msg)
{
    CDuiString sCtrlName = msg.pSender->GetName();

    if (sCtrlName == _T("SetCloudControlRole"))
    {
        int ret = -1;
        tstring role = DebugSetting::GetInstance().GetCloudRole();
        if (!role.empty()) {
            ret = QHVC::INTERACT::QHVCInteract::SetCloudControlRole(STR2A(role).c_str());
        }
        SetTextInfo(_T("SetCloudControlRole:") + role , ret);
    }
    else if (sCtrlName == _T("MuteAllRemoteVideoStreams"))
    {
        m_bAllVideoMute = !m_bAllVideoMute;
        int ret = QHVC::INTERACT::QHVCInteract::MuteAllRemoteVideoStreams(m_bAllVideoMute);
        SetTextBoolInfo(_T("MuteAllRemoteVideoStreams"), m_bAllVideoMute, ret);
    }
    else if (sCtrlName == _T("MuteAllRemoteAudioStreams"))
    {
        m_bAllAudioMute = !m_bAllAudioMute;
        int ret = QHVC::INTERACT::QHVCInteract::MuteAllRemoteAudioStreams(m_bAllAudioMute);
        SetTextBoolInfo(_T("MuteAllRemoteAudioStreams"), m_bAllAudioMute, ret);
    }
    else if (sCtrlName == _T("EnableAudioVolumeIndication"))
    {
        m_bAudioVolumeIndication = !m_bAudioVolumeIndication;
        int interval = m_bAudioVolumeIndication ? 1000 : 0;

        int ret = QHVC::INTERACT::QHVCInteract::EnableAudioVolumeIndication(interval, 10);
        SetTextBoolInfo(_T("EnableAudioVolumeIndication"), m_bAudioVolumeIndication, ret);
    }
    else if (sCtrlName == _T("EnableDualStreamMode"))
    {
        m_bDualStreamMode = !m_bDualStreamMode;

        int ret =QHVC::INTERACT::QHVCInteract::EnableDualStreamMode(m_bDualStreamMode);
        SetTextBoolInfo(_T("EnableDualStreamMode"), m_bDualStreamMode, ret);
    }
    else if (sCtrlName == _T("SetLowStreamVideoProfile"))
    {
        int ret = QHVC::INTERACT::QHVCInteract::SetLowStreamVideoProfile(320, 180, 15, 200);
        SetTextInfo(_T("SetLowStreamVideoProfile:"), ret);
    }
    else if (sCtrlName == _T("SetRemoteVideoStream"))
    {
        m_bRomoteStreamLow = !m_bRomoteStreamLow;
        QHVC::INTERACT::VIDEO_STREAM_LEVEL level = QHVC::INTERACT::VIDEO_STREAM_LEVEL_HIGH;
        if (m_bRomoteStreamLow) {
            level = QHVC::INTERACT::VIDEO_STREAM_LEVEL_LOW;
        }
        else {
            level = QHVC::INTERACT::VIDEO_STREAM_LEVEL_HIGH;
        }

        int ret = -1;
        std::string userId = STR2A(InteractGlobalManager::GetInstance().GetInteractUserId());
        for (int i = 0; i < (int)m_vectAnchorID.size(); i++) {
            if (strcmp(userId.c_str(), m_vectAnchorID[i].c_str()) != 0) {
                ret = QHVC::INTERACT::QHVCInteract::SetRemoteVideoStream(m_vectAnchorID[i].c_str(), level);
            }
        }
        SetTextBoolInfo(_T("SetRemoteVideoStream"), m_bRomoteStreamLow, ret);
    }
    else if (sCtrlName == _T("EnableAudio"))
    {
        m_bEnableAudio = true;
        int ret =QHVC::INTERACT::QHVCInteract::EnableAudio();
        SetTextBoolInfo(_T("EnableAudio"), m_bEnableAudio, ret);
    }
    else if (sCtrlName == _T("DisableAudio"))
    {
        m_bEnableAudio = false;
        int ret = QHVC::INTERACT::QHVCInteract::DisableAudio();
        SetTextBoolInfo(_T("DisableAudio"), m_bEnableAudio, ret);
    }
    else if (sCtrlName == _T("EnableVideo"))
    {
        m_bEnableVideo = true;
        int ret = QHVC::INTERACT::QHVCInteract::EnableVideo();
        SetTextBoolInfo(_T("EnableVideo"), m_bEnableVideo, ret);
    }
    else if (sCtrlName == _T("DisableVideo"))
    {
        m_bEnableVideo = false;
        int ret = QHVC::INTERACT::QHVCInteract::DisableVideo();
        SetTextBoolInfo(_T("DisableVideo"), m_bEnableVideo, ret);
    }
    else if (sCtrlName == _T("ClearVideoCompositingLayout"))
    {
        int ret = QHVC::INTERACT::QHVCInteract::ClearVideoCompositingLayout();
        SetTextInfo(_T("ClearVideoCompositingLayout"), ret);
    }
    else if (sCtrlName == _T("GetEffectsVolume"))
    {
        int ret = QHVC::INTERACT::QHVCInteract::GetEffectsVolume();
        std::string  info;
        info = Util::String::StrFormat("GetEffectsVolume, ret=%d", ret);
        SetTextInfo(STR2T(info));
    }

    else if (sCtrlName == _T("SetEffectsVolume"))
    {
        if (m_nEffectVolume == 100) {
            m_nEffectVolume = 10;
        }
        else {
            m_nEffectVolume = 100;
        }
        int ret = QHVC::INTERACT::QHVCInteract::SetEffectsVolume(m_nEffectVolume);
        std::string  info;
        info = Util::String::StrFormat("SetEffectsVolume, volume=%d, ret=%d", m_nEffectVolume, ret);
        SetTextInfo(STR2T(info));
    }
    else if (sCtrlName == _T("SetVolumeOfEffect"))
    {
        if (m_nEffect1Volume == 100) {
            m_nEffect1Volume = 10;
        }
        else {
            m_nEffect1Volume = 100;
        }

        int ret = QHVC::INTERACT::QHVCInteract::SetVolumeOfEffect(SOUNDID1, m_nEffect1Volume);
        std::string  info;
        info = Util::String::StrFormat("SetVolumeOfEffect, volume=%d, ret=%d", m_nEffect1Volume, ret);
        SetTextInfo(STR2T(info));
    }
    else if (sCtrlName == _T("PlayEffect"))
    {
        if (!m_bEffect1Loaded) {
            if (_access(m_strEffectPath1.c_str(), 0) != 0) {
                std::string msg = "文件不存在：" + m_strEffectPath1;
                DuiMessageBox(m_hWnd, STR2T(msg).c_str(), INTERACT_TITLE, MB_YESNO);
                return;
            }

            int ret = QHVC::INTERACT::QHVCInteract::PlayEffect(SOUNDID1, m_strEffectPath1.c_str(), 100, 1.0, 0, 100.0, true);
            std::string  info;
            info = Util::String::StrFormat("PlayEffect, path = %s, ret=%d", m_strEffectPath1.c_str(), ret);
            SetTextInfo(STR2T(info));
            m_bEffect1Loaded = true;
            return;
        }

        if (!m_bEffect2Loaded) {
            if (_access(m_strEffectPath2.c_str(), 0) != 0) {
                std::string msg = "文件不存在：" + m_strEffectPath2;
                DuiMessageBox(m_hWnd, STR2T(msg).c_str(), INTERACT_TITLE, MB_YESNO);
                return;
            }

            int ret = QHVC::INTERACT::QHVCInteract::PlayEffect(SOUNDID2, m_strEffectPath2.c_str(), 100, 1.0, 0, 100.0, true);
            std::string  info;
            info = Util::String::StrFormat("PlayEffect, path = %s, ret=%d", m_strEffectPath2.c_str(),  ret);
            SetTextInfo(STR2T(info));
            m_bEffect2Loaded = true;
        }
    }
    else if (sCtrlName == _T("StopEffect"))
    {
        int ret = QHVC::INTERACT::QHVCInteract::StopEffect(SOUNDID1);
        std::string  info;
        info = Util::String::StrFormat("StopEffect, ret=%d", ret);
        SetTextInfo(STR2T(info));
        m_bEffect1Loaded = false;
    }
    else if (sCtrlName == _T("StopAllEffects"))
    {
        int ret = QHVC::INTERACT::QHVCInteract::StopAllEffects();
        std::string  info;
        info = Util::String::StrFormat("StopAllEffects, ret=%d", ret);
        SetTextInfo(STR2T(info));
        m_bEffect1Loaded = false;
        m_bEffect2Loaded = false;
    }
    else if (sCtrlName == _T("PreloadEffect"))
    {
        if (_access(m_strEffectPath1.c_str(), 0) != 0) {
            std::string msg = "文件不存在：" + m_strEffectPath1;
            DuiMessageBox(m_hWnd, STR2T(msg).c_str(), INTERACT_TITLE, MB_YESNO);
            return;
        }

        int ret = QHVC::INTERACT::QHVCInteract::PreloadEffect(SOUNDID1, m_strEffectPath1.c_str());
        std::string  info;
        info = Util::String::StrFormat("PreloadEffect, ret=%d", ret);
        SetTextInfo(STR2T(info));
    }
    else if (sCtrlName == _T("UnloadEffect"))
    {
        int ret = QHVC::INTERACT::QHVCInteract::UnloadEffect(SOUNDID1);
        std::string  info;
        info = Util::String::StrFormat("UnloadEffect, ret=%d", ret);
        SetTextInfo(STR2T(info));
        m_bEffect1Loaded = FALSE;
    }
    else if (sCtrlName == _T("PauseEffect"))
    {
        int ret = QHVC::INTERACT::QHVCInteract::PauseEffect(SOUNDID1);
        std::string  info;
        info = Util::String::StrFormat("PauseEffect, ret=%d", ret);
        SetTextInfo(STR2T(info));
    }
    else if (sCtrlName == _T("PauseAllEffects"))
    {
        int ret = QHVC::INTERACT::QHVCInteract::PauseAllEffects();
        std::string  info;
        info = Util::String::StrFormat("PauseAllEffects, ret=%d", ret);
        SetTextInfo(STR2T(info));
    }
    else if (sCtrlName == _T("ResumeEffect"))
    {
        int ret = QHVC::INTERACT::QHVCInteract::ResumeEffect(SOUNDID1);
        std::string  info;
        info = Util::String::StrFormat("ResumeEffect, ret=%d", ret);
        SetTextInfo(STR2T(info));
    }
    else if (sCtrlName == _T("ResumeAllEffects"))
    {
        int ret = QHVC::INTERACT::QHVCInteract::ResumeAllEffects();
        std::string  info;
        info = Util::String::StrFormat("ResumeAllEffects, ret=%d", ret);
        SetTextInfo(STR2T(info));
    }
    Super::OnClick(msg);
}

void CInteractTestDlg::SetAnchorIDList(const std::vector<std::string >& vectAnchorID)
{
    m_vectAnchorID = vectAnchorID;
}

void CInteractTestDlg::SetInteractRoomModel(const InteractRoomModel& interactRoomModel)
{
    mInteractRoomModel = interactRoomModel;
}

void CInteractTestDlg::SetTextBoolInfo(const tstring& info, bool bValue, int ret)
{
    tstring log = info;
    if (bValue) {
        log.append(_T("set value :true"));
    }
    else {
        log.append(_T("set value :false"));
    }

    log.append(STR2T(Util::String::StrFormat(" ret=%d", ret)));

    CLabelUI* pLabelInfo = static_cast<CLabelUI*>(FindControl(_T("lb_text_info")));
    if (pLabelInfo) {
        pLabelInfo->SetText(log.c_str());
    }
}

void CInteractTestDlg::SetTextInfo(const tstring& info, int ret)
{
    tstring log = info;

    log.append(STR2T(Util::String::StrFormat(" ret=%d", ret)));

    CLabelUI* pLabelInfo = static_cast<CLabelUI*>(FindControl(_T("lb_text_info")));
    if (pLabelInfo) {
        pLabelInfo->SetText(log.c_str());
    }
}

void CInteractTestDlg::SetTextInfo(const tstring& info)
{
    CLabelUI* pLabelInfo = static_cast<CLabelUI*>(FindControl(_T("lb_text_info")));
    if (pLabelInfo) {
        pLabelInfo->SetText(info.c_str());
    }
}
