#ifndef _QHVC_INTERACT_H_
#define _QHVC_INTERACT_H_

#pragma once

#include "QHVCSdk.h"
#include "QHVCInteractCallback.h"
#include "QHVCInteractConstant.h"

namespace QHVC
{
    namespace INTERACT
    {
        namespace QHVCInteract {

            /**
            * ��ȡSDK�汾��
            *
            * @return SDK�汾��
            */
            QHVC_API const char* GetVersion();

#pragma region ��������

            /**
            * ���ù���ҵ����Ϣ�÷�����Ҫ������ʵ������֮ǰ���ã���������ҵ������Ҫ��һЩ��Ҫ��Ϣ������ҵ�����֡�ͳ��ʹ�á�
            *
            * @param channelId ����Id���������ֹ�˾������ӵ�ж��Ӧ�á���ֱ����ΪӦ�ó��򿪷���ǩ�������û�У�����ֱ�������롣
            * @param appKey ֱ����ΪӦ�ó��򿪷���ǩ����App Key�����û�У�����ֱ�������롣
            * @param userSign  �û�ǩ��������������ֱ�����ṩ���㷨���ɴ� User Sign�����ڷ��������û���֤��
            */
            QHVC_API void SetPublicServiceInfo(const char* channelId, const char*  appKey, const char*  userSign);

            /**
            * ���ػ���ֱ���������ݣ�����׼�����������ø÷���ǰ�������ȵ���setPublicServiceInfo����ҵ����Ϣ׼����
            * �����ڸ÷������ú���ܵ�������ʵ���������÷������첽ִ�У����ص�ִ��֮�����ִ������ʵ��������
            *
            * @param roomId           ����Id��������64�ֽ����ڵ��ַ���������Ϊ֧�ֵ��ַ�����Χ: a-z,A-Z,0-9
            * @param userId           �û�id, ע�⣺****�����������֣����9λ���֣�����֤Ψһ��
            * @param sessionId        �ỰID�����ڱ�ʶҵ��Ự����ÿһ������������֮�󣬸�ֵ��Ҫ��������
            * @param optionInfo       ��ѡ�ֵ䣬ʹ��json����������·ֱ�����ܵȿ�ͨ�����ֵ����ã����ҵ��׼��ʹ����Ƶ�Ƶ�ֱ������
            *                         ����ͨ��applyforBypassLiveAddress�ӿ�������������
            *                         ����: {"push_addr":"xxx", "pull_addr";"xxxx"},��������μ�
            *                         {@link QHVC#INTERACT#ENGINE_OPTION}���塣
            * @param interactCallBack �ص�
            * @return 0:��ʾ�ɹ�,������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int LoadEngine(const char*  roomId, const char*  userId, const char*  sessionId, const char* optionInfo,
                const IQHVCInteractCallback* interactCallBack);

            /**
            * �ͷ���������
            */
            QHVC_API void ReleaseEngine();


            /**
            * �÷������û�����ͨ��Ƶ������ͬһ��Ƶ���ڵ��û����Ի���ͨ��������û�����ͬһ��Ƶ����
            * ����Ⱥ�ġ��������ͨ���У��û��������leaveChannel �˳���ǰͨ�������ܽ�����һ��Ƶ����
            *
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int JoinChannel();


            /**
            * �뿪Ƶ��
            * ���Ҷϻ��˳�ͨ����joinChannel�󣬱������leaveChannel�Խ���ͨ���������ܽ�����һ��ͨ�������ܵ�ǰ
            * �Ƿ���ͨ���У������Ե���leaveChannel��û�и����á�leaveChannel��ѻỰ��ص�������Դ�ͷŵ���leaveChannel
            * ���첽���������÷���ʱ��û�������˳�Ƶ�����������˳�Ƶ����SDK�ᴥ��IQHVCInteractCallBack.onLeaveChannel()��
            *
            * @return 0 �ɹ�, ������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int LeaveChannel();

            /**
            * �÷�����������Ƶ��ģʽ(Profile)�� SDK��֪��Ӧ�ó����ʹ�ó����� �Ӷ�ʹ��
            * ��ͬ���Ż��ֶΡ�
            * ע��
            *     1. ͬһƵ����ֻ��ͬʱ����һ��ģʽ��
            *     2. �÷��������ڽ���Ƶ��ǰ���ã���Ƶ����������Ч��
            *
            * @param profile ָ��Ƶ����ͨ��ģʽ(profile)��֧������ģʽ��
            *                QHVC#INTERACT#CHANNEL_PROFILE_COMMUNICATION (ͨ��ģʽ��Ĭ��)
            *                QHVC#INTERACT#CHANNEL_PROFILE _LIVE_BROADCASTING (ֱ��ģʽ)
            *                QHVC#INTERACT#CHANNEL_PROFILE_GAME (��Ϸ����ģʽ)
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetChannelProfile(CHANNEL_PROFILE profile);

            /**
            * ������Ƶģʽ, �÷������ڿ�����Ƶģʽ�������ڼ���Ƶ��ǰ����ͨ���е��ã��ڼ���Ƶ��ǰ���ã����Զ���
            * ����Ƶģʽ����ͨ���е���������Ƶģʽ�л�Ϊ��Ƶģʽ������ disablevideo �����ɹر���
            * Ƶģʽ��
            *
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int EnableVideo();

            /**
            * ��������Ƶģʽ, �÷������ڹر���Ƶ����������Ƶģʽ�������ڼ���Ƶ��ǰ����ͨ���е��ã��ڼ���Ƶ��ǰ��
            * �ã����Զ���������Ƶģʽ����ͨ���е���������Ƶģʽ�л�Ϊ����ƵƵģʽ������
            * enablevideo �����ɿ�����Ƶģʽ��
            *
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int DisableVideo();

            /**
            * ����/���ñ�����Ƶ���ܡ��÷�������ֻ����������Ƶ�������÷�������Ҫ����������ͷ��
            *
            * @param enabled true: ���ñ�����Ƶ��Ĭ�ϣ� false: ���ñ�����Ƶ
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int EnableLocalVideo(bool enabled);

            /**
            * �÷��������û�������Ƶ���Ż�ѡ�
            *
            * @param preferFrameRateOverImageQuality true: ���ʺ�����������ȱ�֤����(Ĭ��),false: ���ʺ�����������ȱ�֤������
            * @return 0 �ɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetVideoQualityParameters(bool preferFrameRateOverImageQuality);

            /**
            * �÷�����������������ƵԤ�����ڿ���Ԥ��ǰ�������ȵ��� setupLocalVideo ����Ԥ�����ڼ�
            * ���ԣ��ұ������ enableVideo ������Ƶ���ܡ�����ڵ��� joinChannel ����Ƶ��֮ǰ������
            * startPreview ����������ƵԤ�����ڵ��� leaveChannel �˳�Ƶ��֮�󱾵�Ԥ����Ȼ��������
            * ״̬������Ҫ�رձ���Ԥ������Ҫ���� stopPreview��
            * ע����������������ʹ��SDK�ɼ���Ƶ������ҵ����Բɼ���Ƶʱ���벻Ҫ���á�
            *
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int StartPreview();

            /**
            * �÷�������ֹͣ������ƵԤ����
            *
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int StopPreview();

            /**
            * ��������ģʽ
            * �÷�����������ģʽ(Ĭ��Ϊ����״̬)��
            *
            * @return 0 �ɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int EnableAudio();

            /**
            * �ر�����ģʽ
            *
            * @return 0 �ɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int DisableAudio();

            /**
            * ��������
            * �÷�������������Ƶ�����ʡ����뷽ʽ�����������������ʣ��Լ�ʹ�ó�����
            * ע��1. �÷�����Ҫ�� joinChannel ֮ǰ���úã�joinChannel ֮�����ò���Ч
            *     2. ͨ��ģʽ�£��÷������� profile ��Ч������ scenario ����Ч
            *     3. ͨ�ź�ֱ��ģʽ�£����ʣ����ʣ�������������Ӧ�ĵ�����ͨ���÷������õ���һ���������
            *
            * @param profile ��Ƶ�����ʡ����뷽ʽ������������������
            * @param scenario ��ƵӦ�ó���
            * @return 0 �ɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetAudioProfile(AUDIO_PROFILE profile, AUDIO_SCENARIO scenario);

            /**
            * ����һЩSDK���������
            *
            * @param options ������json��ʽ
            * @return 0 �ɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetParameters(const char* options);

            /**
            * ���ú��л��û�ģʽ
            * �ڼ���Ƶ��ǰ���û���Ҫͨ�����������ù��ڻ�����ģʽ��Ĭ�ϣ���
            * �ڼ���Ƶ�����û�����ͨ���������л��û�ģʽ��
            * �÷�������ֱ��ģʽ��Ч��
            *
            * @param role ֱ�����û���ɫ�� QHVC#INTERACT#CLIENT_ROLE_BROADCASTER :����
            *             QHVC#INTERACT#CLIENT_ROLE_GUEST �α�
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetClientRole(CLIENT_ROLE role);

            /**
            * �����������ɫ
            *
            * @param role �������ɫ���ƣ���Ҫ����Ƶ������������һ�£���������б�������������
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetCloudControlRole(const char* role);

            /**
            * �÷������ñ�����Ƶ��ʾ��Ϣ��Ӧ�ó���ͨ�����ô˽ӿڰ󶨱�����Ƶ������ʾ�Ӵ�(view)��
            * ��������Ƶ��ʾģʽ����Ӧ�ó��򿪷��У� ͨ���ڳ�ʼ������ø÷������б�����Ƶ���ã�
            * Ȼ���ټ���Ƶ�����˳�Ƶ���󣬰���Ȼ��Ч�������Ҫ����󶨣�����ָ����(NULL)View
            * ���� setupLocalVideo��
            *
            * @param view       ��Ƶ��ʾ�Ӵ���
            * @param renderMode ��Ƶ��ʾģʽ��
            *                   QHVC#INTERACT#RENDER_MODE_HIDDEN (1): �����Ƶ�ߴ�����ʾ�Ӵ��ߴ粻һ�£�����Ƶ���ᰴ����ʾ�Ӵ��ı��������ܱ߲ü���ͼ������������Ӵ���
            *                   QHVC#INTERACT#ENDER_MODE_FIT(2): �����Ƶ�ߴ�����ʾ�Ӵ��ߴ粻һ�£��ڱ��ֳ����ȵ�ǰ���£�����Ƶ�������ź������Ӵ���
            *                   QHVC#INTERACT#RENDER_MODE_ADAPTIVE(3)������Լ��ͶԷ�������������������Լ��ͶԷ����Ǻ�����ʹ��RENDER_MODE_HIDDEN������Է����Լ�һ��
            *                   ����һ����������ʹ�� RENDER_MODE_FIT��
            * @param uid        �����û�ID, �� joinchannel �����е� uid ����һ�¡�
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetupLocalVideo(HWND view, RENDER_MODE renderMode, const char* uid);

            /**
            * �÷�����Զ���û�����ʾ��ͼ�����趨 uid ָ�����û����ĸ���ͼ����ʾ��һ·����������ҵ���������ʲôʱ����ʾ�����ĳ���û��İ���ͼ���Ե���removeRemoteVideo��
            * �˳�Ƶ���� SDK ���Զ���û��İ󶨹�ϵ�������
            *
            * @param view       ��Ƶ��ʾ�Ӵ���
            * @param renderMode ��Ƶ��ʾģʽ��
            *                   QHVC#INTERACT#RENDER_MODE_HIDDEN (1): �����Ƶ�ߴ�����ʾ�Ӵ��ߴ粻һ�£�����Ƶ���ᰴ����ʾ�Ӵ��ı��������ܱ߲ü���ͼ������������Ӵ���
            *                   QHVC#INTERACT#RENDER_MODE_FIT(2): �����Ƶ�ߴ�����ʾ�Ӵ��ߴ粻һ�£��ڱ��ֳ����ȵ�ǰ���£�����Ƶ�������ź������Ӵ���
            *                   QHVC#INTERACT#RENDER_MODE_ADAPTIVE(3)������Լ��ͶԷ�������������������Լ��ͶԷ����Ǻ�����ʹ�� RENDER_MODE_HIDDEN������Է����Լ�һ������һ����������ʹ��RENDER_MODE_FIT��
            * @param uid        �û� ID��ָ��Զ����Ƶ�����ĸ��û���
            * @param streamId   ��ID��ָ��Զ����Ƶ����ID
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetupRemoteVideo(HWND view, RENDER_MODE renderMode, const char* uid, const char* streamId);

            /**
            * �÷������ڽ��Զ���û�����ʾ��ͼ����Զ���û��뿪Ƶ���󣬵��ô˷��������
            *
            * @param streamId ָ��Զ����Ƶ����ID
            * @param uid      �û�ID��ָ��Զ����Ƶ�����ĸ��û�
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int RemoveRemoteVideo(const char* streamId, const char* uid);

            /**
            * �÷������ñ�����Ƶ��ʾģʽ��Ӧ�ó�����Զ�ε��ô˷���������ʾģʽ��
            * ע����������������ʹ��SDK�ɼ���Ƶ������ҵ����Բɼ���Ƶʱ���벻Ҫ���á�
            *
            * @param mode ������Ƶ��ʾģʽ��
            *             QHVC#INTERACT#RENDER_MODE_HIDDEN (1): �����Ƶ�ߴ�����ʾ�Ӵ��ߴ粻һ�£�����Ƶ���ᰴ����ʾ�Ӵ��ı��������ܱ߲ü���ͼ������������Ӵ���
            *             QHVC#INTERACT#RENDER_MODE_FIT(2): �����Ƶ�ߴ�����ʾ�Ӵ��ߴ粻һ�£��ڱ��ֳ����ȵ�ǰ���£�����Ƶ�������ź������Ӵ���
            *             QHVC#INTERACT#RENDER_MODE_ADAPTIVE(3)������Լ��ͶԷ�������������������Լ��ͶԷ����Ǻ�����ʹ��RENDER_MODE_HIDDEN������Է����Լ�һ������һ����������ʹ�� RENDER_MODE_FIT��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetLocalRenderMode(RENDER_MODE mode);

            /**
            * �÷������ñ�����Ƶ�������ڿ�������Ԥ��ǰ���á�����ڿ���Ԥ�������ã���Ҫ���¿���Ԥ��������Ч��
            * ��SetupRemoteVideoǰ����
            * @param mode ����ģʽ���͡�����@link QHVC#INTERACT#VIDEO_MIRROR_MODE��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetLocalVideoMirrorMode(VIDEO_MIRROR_MODE mode);

            /**
            * �÷�������Զ����Ƶ��ʾģʽ��Ӧ�ó�����Զ�ε��ô˷���������ʾģʽ��
            *
            * @param uid  �û� ID
            * @param mode ������Ƶ��ʾģʽ��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetRemoteRenderMode(const char*  uid, RENDER_MODE mode);

            /**
            * �÷���������Ƶ��������(Profile)��ÿ�����Զ�Ӧһ����Ƶ��������ֱ��ʡ�֡�ʡ����ʵȡ����豸������ͷ
            * ��֧��ָ���ķֱ���ʱ�� SDK ���Զ�ѡ��һ�����ʵ�����ͷ�ֱ��ʣ����Ǳ���ֱ�����Ȼ�� setVideoProfile ָ���ġ�
            * ע��
            *       1. Ӧ�ڵ��� joinChannel/startPreview ǰ������Ƶ���ԡ�
            *       2. �÷��������ñ�����������������ԣ����ܸ�������ʾ�����Բ�һ�£�������������ֱ���Ϊ 640x480������
            *       ����ת����Ϊ 90 �ȣ�����ʾ�����ķֱ���Ϊ����ģʽ��
            *
            * @param profile            ��Ƶ����(Profile)�����QHVCInteractConstant.VideoProfile�еĶ��塣
            * @param swapWidthAndHeight �Ƿ񽻻����͸ߡ�    true���������͸�  false�����������͸�(Ĭ��)
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetVideoProfile(VIDEO_PROFILE profile, bool swapWidthAndHeight);

            /**
            * �÷���������Ƶ��������
            *
            * @param width ��Ƶ�ֱ���-��
            * @param height ��Ƶ�ֱ���-��
            * @param frameRate ��Ƶ֡��
            * @param bitrate ��Ƶ����
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetVideoProfileEx(int width, int height, int frameRate, int bitrate);

            /**
            * ��ͣ/�ָ����ͱ�����Ƶ�����÷�����������/��ֹ�����緢�ͱ�����Ƶ����
            * ע�� �÷�����Ӱ�챾����Ƶ����ȡ��û�н�������ͷ��
            *
            * @param muted True: �����ͱ�����Ƶ��  False: ���ͱ�����Ƶ��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int MuteLocalVideoStream(bool muted);

            /**
            * ��ͣ/�ָ���������Ƶ������������������/��ֹ���������˵���Ƶ����
            * ע�� �÷�����Ӱ����Ƶ�������Ľ��գ�ֻ�ǲ�������Ƶ����
            *
            * @param muted True: ֹͣ���Ž��յ���������Ƶ�� False: �������Ž��յ���������Ƶ��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int MuteAllRemoteVideoStreams(bool muted);

            /**
            * ��ͣ/�ָ�ָ��Զ����Ƶ������������������/��ֹ����ָ��Զ����Ƶ����
            * ע�� �÷�����Ӱ����Ƶ�������Ľ��գ�ֻ�ǲ�������Ƶ����
            *
            * @param uid   ָ���û�
            * @param muted True: ֹͣ���Ž��յ�����Ƶ�� False: �������Ž��յ�����Ƶ��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int MuteRemoteVideoStream(const char* uid, bool muted);

            /**
            * ����˵����������ʾ���÷������� SDK ������Ӧ�ó�������ǰ˭��˵���Լ�˵���ߵ�����
            *
            * @param interval ָ��������ʾ��ʱ����
            *                 <= 0������������ʾ����
            *                 > 0������������ʾ�ļ������λΪ���롣�������õ����� 200 ���롣
            *                 ���ø÷���������Ƶ�����Ƿ�����˵����������˵������������ʾ�ص� (onAudioVolumeIndication) �ص��а����õļ��ʱ�䷵��������ʾ
            * @param smooth ƽ��ϵ����Ĭ�Ͽ�������Ϊ3
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int EnableAudioVolumeIndication(int interval, int smooth);

            /**
            * ����/ȡ���������÷�����������/��ֹ�����緢�ͱ�����Ƶ����
            * ע�� �÷�����Ӱ��¼��״̬����û�н�����˷硣
            *
            * @param muted True����˷羲��  False��ȡ������
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int MuteLocalAudioStream(bool muted);

            /**
            * ��������Զ���û�/������Զ���û�ȡ����������������������/��ֹ����Զ���û�����Ƶ����
            * ע�� �÷�����Ӱ����Ƶ�������Ľ��գ�ֻ�ǲ�������Ƶ����
            *
            * @param muted True����˷羲��  False��ȡ������
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int MuteAllRemoteAudioStreams(bool muted);

            /**
            * ����ָ��Զ���û�/��ָ��Զ���û�ȡ����������������������/��ֹ����Զ���û�����Ƶ����
            * ע�� �÷�����Ӱ����Ƶ�������Ľ��գ�ֻ�ǲ�������Ƶ����
            *
            * @param uid   ָ���û�
            * @param muted True����˷羲�� False��ȡ������
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int MuteRemoteAudioStream(const char* uid, bool muted);

#pragma endregion ��������

#pragma region ˫�����

            /**
            * ʹ��˫��/����ģʽ
            *
            * @param enabled ָ��˫�����ߵ���ģʽ true��˫�� false��������Ĭ�ϣ�
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int EnableDualStreamMode(bool enabled);

            /**
            * ����С���Ĳ��������ڿ���˫��ģʽʱ��Ч��
            * С���ֱ�����Ҫ�ʹ����ĳɱ������������ 360*640��С���������� 180*320��С����Ҫ����̫��
            * ע�� ��ȷ����joinChannel֮ǰ���á�
            *
            * @param width   ��Ƶ�Ŀ���
            * @param height  ��Ƶ�Ŀ���
            * @param fps     ֡��
            * @param bitrate ���� (��λ��kbps)
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetLowStreamVideoProfile(int width, int height, int fps, int bitrate);

            /**
            * ��Ƶ��С���л�, �÷���ָ������Զ���û�����Ƶ����С��ʹ�ø÷������Ը�����Ƶ���ڵĴ�С��̬������Ӧ
            * ��Ƶ���Ĵ�С���Խ�Լ�����ͼ�����Դ������������״̬�������ĵ�SDK Ĭ���յ���ƵС������ʡ������
            * ����ʹ����Ƶ���������ñ����������л���
            *
            * @param uid         �û� ID
            * @param streamLevel ������Ƶ����С��QHVCInteractConstant.VIDEO_STREAM_LEVEL_HIGH (0): ��Ƶ����
            *                                    QHVCInteractConstant.VIDEO_STREAM_LEVEL_LOW (1): ��ƵС��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetRemoteVideoStream(const char* uid, VIDEO_STREAM_LEVEL streamLevel);

#pragma endregion ˫�����

#pragma region �������

            /**
            * N+1·ת�ƣ�1·����+N·��������������ϢԤ��ӿ�
            * ��ȷ��Ҫ��joinChannel֮ǰ���á�
            *
            * @param mixStreamConfig ��������
            * @param streamLifeCycle ����������������ڣ����԰�������󶨷���
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetMixStreamInfo(const MixStreamConfig* mixStreamConfig, STREAM_LIFE_CYCLE streamLifeCycle);

            /**
            * ת��N+1·��ʱ�����º�������Ƶ����
            * ע��1. ��ȷ����IQHVCInteractCallBack.onFirstRemoteVideoFrame()�ӿ��У���֮�󣩣����ø÷�����
            *     2��count ���10
            *
            * @param mixStreamInfos ������Ϣ����ȷ���������е���Ƶ����������������Ƶ����
            * @param count mixStreamInfos����Ĵ�С��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetVideoCompositingLayout(const MixStreamRegion* mixStreamInfos, int count);

            /**
            * ȡ����������
            *
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int ClearVideoCompositingLayout();

#pragma endregion �������

#pragma region ����Ⱦ���Բɼ����
            /**
            * ���ñ�����Ƶ�ⲿ��Ⱦ����ҵ�����Ⱦ������Ƶ���ݻص��ӿ�
            * @param pCallback ������Ƶ�ص���callback������ͨ�������ص����������زɼ���Ƶ�����ݣ���ʵ�����ա�����Ⱦ�������滻���Բɼ����ȣ�@link QHVC#INTERACT#IQHVCInteractLocalVideoRenderCallback��
            *
            * @return 0:  �������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */

            QHVC_API int SetLocalVideoRenderCallback(IQHVCInteractLocalVideoRenderCallback* pCallback);

            /**
            * ����Զ����Ƶʹ���ⲿ��Ⱦ
            * @param uid                    �û� ID��ָ��Զ����Ƶ�����ĸ��û���
            * @param streamId               ��id
            *
            * @return 0:  �������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetRemoteVideoExternalRender(const char* userId, const char* streamId);

            /**
            * ����Զ����Ƶ�ⲿ��Ⱦ����ҵ�����Ⱦ������Ƶ�ص��ӿ�
            * @param pCallback Զ����Ƶ�ص���callback�� ����ͨ�������ص���ʵ������Ⱦ�ȣ�@link QHVC#INTERACT#IQHVCInteractRemoteVideoRenderCallback��
            *
            * @return 0:  �������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */

            QHVC_API int SetRemoteVideoRenderCallback(IQHVCInteractRemoteVideoRenderCallback* pCallback);

            /**
            * �÷���������Ƶ���ݶ���ص���callback
            * @param pCallback �������ݻص���@link QHVC#INTERACT#IQHVCInteractAudioFrameCallback��
            *
            * @return 0:  �������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */

            QHVC_API int SetAudioFrameCallback(IQHVCInteractAudioFrameCallback* pCallback);


            /**
            * ����ҵ������Ƶ���ݲɼ���ȷ����{@link #LoadEngine}����ǰ���ã�Ĭ�Ϲرա�
            */

            QHVC_API int OpenCollectingData();

            /**
            * �ر����ݲɼ���ȷ����{@link #LoadEngine}����ǰ����
            */
            QHVC_API int CloseCollectingData();


            /**
            * �÷�����sdk�����Բɼ�������
            * @param videoFrame ��Ƶ����
            *
            * @return 0:  �������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */

            QHVC_API int IncomingCollectingCapturedData(VideoFrame* videoFrame);
#pragma endregion ����Ⱦ���Բɼ����

#pragma region ��Ƶ�߼��ӿ�-��Ļ����

            /**
            * ������Ļ�������÷�������������Ļ��ָ�����ڣ���ָ������:
            *     ����������Ļ: �� hWnd ��Ϊ 0���ҽ� rect ��Ϊ null
            *     ����ָ������: �� hWnd ��Ϊ�� 0��ÿ�����ڶ���һ���� 0 �� hWnd
            *     ����ָ������: �� hWnd ��Ϊ 0���ҽ� rect ��Ϊ�� null������� ����ָ������ ָ���ǹ���������Ļ���ĳ������Ŀǰ�ݲ�֧�ֹ���ָ���������ָ������
            *
            * @param hWnd ���ھ����Ϊ��ʱ��ʾ������Ļ
            * @param captureFreq ������Ļ��֡�ʣ�ȡֵ1~15
            * @param rect ��Ļָ�����򣬽��� hWnd=null ʱ��Ч
            * @param bitrate ������Ļ�����ʣ���λkbps��������Ϊ0����SDK���ݹ�����Ļ�ķֱ��ʼ�֡�ʼ�������
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int StartScreenCapture(HWND hWnd, int captureFreq, const RECT* rect, int bitrate = 0);

            /**
            * ֹͣ��Ļ����
            *
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int StopScreenCapture();

            /**
            * ������Ļ��ͼ����
            *
            * @param rect ֻ���ڵ��� startScreenCapture() ʱ�� hWnd ��Ϊ 0 ʱ���ò�������Ч���� rect ����Ϊ null ʱ, ����������Ļ
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int UpdateScreenCaptureRegion(const RECT *rect);

#pragma endregion ��Ƶ�߼��ӿ�-��Ļ����

#pragma region ��Ƶ�߼��ӿ�-����

            /**
            * ��ʼ���Ű��ָ࣬��������Ƶ�ļ�������˷�ɼ�����Ƶ�����л������滻(����Ƶ�ļ��滻��˷�ɼ�����Ƶ��)��
            * ����ͨ������ѡ���Ƿ��öԷ��������ز��ŵ���Ƶ��ָ��ѭ�����ŵĴ���
            *
            * @param filePath ������Ƶ�ļ�·��
            * @param loopback true �����������������ز��ŵ���Ƶ
            *                 false �������غͶԷ��������ز��ŵ���Ƶ
            * @param replace true ���ز��ŵ���Ƶ�滻��˷�ɼ�����Ƶ
            *                false ���ز��ŵ���Ƶ����˷�ɼ�����Ƶ���л���
            * @param cycle ѭ�����Ŵ�����-1��ʾ����ѭ��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int StartAudioMixing(const char* filePath, bool loopback, bool replace, int cycle);

            /**
            * ֹͣ���Ű���
            *
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int StopAudioMixing();

            /**
            * ��ͣ���Ű���
            *
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int PauseAudioMixing();

            /**
            * �ָ����Ű���
            *
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int ResumeAudioMixing();

            /**
            * ���ڰ�������
            *
            * @param volume ������������Χ0-100��Ĭ��100
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int AdjustAudioMixingVolume(int volume);

            /**
            * ��ȡ����ʱ������λ����
            *
            * @return ���ذ���ʱ����0��ʾʧ��
            */
            QHVC_API int GetAudioMixingDuration();

            /**
            * ��ȡ���ಥ�Ž��ȣ���λ����
            *
            * @return ���ص�ǰ���Ž��ȣ�0��ʾʧ��
            */
            QHVC_API int GetAudioMixingCurrentPosition();

            /**
            * ���ð��ಥ��λ�ã���λ����
            *
            * @param position ����λ�ã���λ����
            * @param
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetAudioMixingPosition(int position);

#pragma endregion

#pragma region ��Ƶ�߼��ӿ�-��Ч
            /**
            * �÷�����ȡ��Ч����������ΧΪ [0.0, 100]��
            * @return ��Ч������
            */
            QHVC_API int GetEffectsVolume();

            /**
            * �÷���������Ч��������
            * @param volume ����, ȡֵ��ΧΪ [0.0, 100]�� 100.0ΪĬ��ֵ
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetEffectsVolume(int volume);

            /**
            * �÷���ʵʱ����ָ����Ч��������
            * @param soundId ָ����Ч�� ID��ÿ����Ч����Ψһ�� ID
            * @param volume ȡֵ��ΧΪ [0.0, 100]�� 100 ΪĬ��ֵ
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int SetVolumeOfEffect(int soundId, int volume);

            /**
            * �÷�������ָ����Ч��
            * @param soundId ָ����Ч�� ID��ÿ����Ч����Ψһ��ID���������ͨ�� preloadEffect ����Ч�������ڴ棬ȷ���������õ� soundId �� preloadEffect ���õ� soundId ��ͬ��
            * @param filePath ��Ч�ļ��ľ���·��
            * @param loopCount ������Чѭ�����ŵĴ�����
            *       0��������Чһ��
            *       1��ѭ��������Ч����
            *       -1������ѭ��������Ч��ֱ������ stopEffect �� stopAllEffects ��ֹͣ
            * @param pitch ������Ч������ ȡֵ��ΧΪ [0.5, 2]��Ĭ��ֵΪ 1.0����ʾ����Ҫ�޸�������ȡֵԽС��������Խ��
            * @param pan   �����Ƿ�ı���Ч�Ŀռ�λ�á�ȡֵ��ΧΪ [-1, 1]��
            *       0����Ч��������ǰ��
            *       -1����Ч���������
            *       1����Ч�������ұ�
            * @param gain �����Ƿ�ı䵥����Ч��������ȡֵ��ΧΪ [0.0, 100.0]��Ĭ��ֵΪ 100.0��ȡֵԽС������Ч������Խ��
            * @param publish �����Ƿ���Ч����Զ�ˣ�
            *       true����Ч�ڱ��ز��ŵ�ͬʱ���ᷢ�������ϣ����Զ���û�Ҳ����������Ч
            *       false����Ч���ᷢ�������ϣ����ֻ���ڱ�����������Ч
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int PlayEffect(int soundId, const char* filePath, int loopCount, double pitch, double pan, double gain, bool publish);

            /**
            * �÷���ֹͣ����ָ����Ч��
            * @param soundId  ָ����Ч�� ID��ÿ����Ч����Ψһ�� ID
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int StopEffect(int soundId);

            /**
            * �÷���ֹͣ����������Ч��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int StopAllEffects();

            /**
            *  Ԥ������Ч
            *  �÷�����ָ����Ч�ļ�(ѹ���������ļ�)Ԥ�������ڴ档
            * @param soundId ָ����Ч�� ID��ÿ����Ч����Ψһ�� ID
            * @param filePath ��Ч�ļ��ľ���·��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int PreloadEffect(int soundId, const char* filePath);

            /**
            * �÷�����ָ��Ԥ���ص���Ч���ڴ����ͷų�����
            * @param soundId  ָ����Ч�� ID��ÿ����Ч����Ψһ�� ID
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int UnloadEffect(int soundId);

            /**
            * �÷�����ͣ����ָ����Ч��
            * @param soundId ָ����Ч�� ID��ÿ����Ч����Ψһ�� ID
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int PauseEffect(int soundId);

            /**
            * �÷�����ͣ����������Ч��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int PauseAllEffects();

            /**
            * �÷����ָ�����ָ����Ч��
            * @param soundId ָ����Ч�� ID��ÿ����Ч����Ψһ��ID��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int ResumeEffect(int soundId);

            /**
            * �ָ�����������Ч��
            * @return 0���������óɹ���������ʾʧ�ܣ�����@link QHVC#INTERACT#ERR��
            */
            QHVC_API int ResumeAllEffects();

#pragma endregion

#pragma region �豸���

            /**
            * �ͷ��豸�б�
            *
            * @param [in] �豸�б�
            */
            QHVC_API void FreeDeviceList(__in DeviceInfo* parrDeviceList);

            /**
            * ��ȡ��Ƶ�豸�б�
            *
            * @param [out] ��Ƶ�豸����
            * @return ��Ƶ�豸�б�
            */
            QHVC_API DeviceInfo* GetVideoDeviceList(__out int& deviceCount);

            /**
            * ��ȡ��ǰ��Ƶ�豸
            *
            * @param deviceId �豸ID
            * @param length deviceId����
            * @return 0 �ɹ��������ο�{@link INTERACT::Err} ����
            */
            QHVC_API int GetVideoDevice(__out char* deviceId, int length);

            /**
            * ���õ�ǰ��Ƶ�豸
            *
            * @param deviceId �豸ID
            * @return 0 �ɹ��������ο�{@link INTERACT::Err} ����
            */
            QHVC_API int SetVideoDevice(__in const char* deviceId);

            /**
            * ��ȡ��Ƶ�豸�б�
            *
            * @param deviceType [in] ��Ƶ�豸���ͣ����������豸
            * @param deviceCount [out] ��Ƶ�豸����
            * @return ��Ƶ�豸�б�
            */
            QHVC_API DeviceInfo* GetAudioDeviceList(__in AUDIO_DEVICE_TYPE deviceType, __out int& deviceCount);

            /**
            * ��ȡ��ǰ��Ƶ�豸
            *
            * @param deviceType [in] ��Ƶ�豸���ͣ����������豸
            * @param deviceId �豸ID
            * @param length deviceId����
            * @return 0 �ɹ��������ο�{@link INTERACT::Err} ����
            */
            QHVC_API int GetAudioDevice(__in AUDIO_DEVICE_TYPE deviceType, __out char* deviceId, int length);

            /**
            * ���õ�ǰ��Ƶ�豸
            *
            * @param deviceType [in] ��Ƶ�豸���ͣ����������豸
            * @param deviceId �豸ID
            * @return 0 �ɹ��������ο�{@link INTERACT::Err} ����
            */
            QHVC_API int SetAudioDevice(__in AUDIO_DEVICE_TYPE deviceType, __in const char* deviceId);

            /**
            * ��ȡ��ǰ��Ƶ�豸����
            *
            * @param deviceType [in] ��Ƶ�豸���ͣ����������豸
            * @param volume [out] ������0~255
            * @return 0 �ɹ��������ο�{@link INTERACT::Err} ����
            */
            QHVC_API int GetAudioDeviceVolume(__in AUDIO_DEVICE_TYPE deviceType, __out int& volume);

            /**
            * ���õ�ǰ��Ƶ�豸����
            *
            * @param deviceType [in] ��Ƶ�豸���ͣ����������豸
            * @param volume [in] ������0~255
            * @return 0 �ɹ��������ο�{@link INTERACT::Err} ����
            */
            QHVC_API int SetAudioDeviceVolume(__in AUDIO_DEVICE_TYPE deviceType, __in int volume);

            /**
            * ��ȡ��ǰ�豸�Ƿ���
            *
            * @param deviceType [in] ��Ƶ�豸���ͣ����������豸
            * @param mute [out] true ������false �Ǿ���
            * @return 0 �ɹ��������ο�{@link INTERACT::Err} ����
            */
            QHVC_API int GetAudioDeviceMute(__in AUDIO_DEVICE_TYPE deviceType, __out bool& mute);

            /**
            * ���õ�ǰ�豸�Ƿ���
            *
            * @param deviceType [in] ��Ƶ�豸���ͣ����������豸
            * @param mute [in] true ������false �Ǿ���
            * @return 0 �ɹ��������ο�{@link INTERACT::Err} ����
            */
            QHVC_API int SetAudioDeviceMute(__in AUDIO_DEVICE_TYPE deviceType, __in bool mute);
#pragma endregion �豸���
        }
    }
}

#endif