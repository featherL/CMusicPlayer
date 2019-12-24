#pragma once

#include <Windows.h>

//·�������ĺ���
#include <Shlwapi.h> 
#pragma comment(lib,"shlwapi.lib")

#include <stdlib.h>

//mci�ӿ�
#include <mmsystem.h>  
#pragma comment (lib, "winmm.lib")

//�궨��
//˳�򲥷š�ѭ�����š��������
#define MODE_ORDER 1
#define MODE_LOOP 2
#define MODE_RANDOWM 3

//����״̬��ֹͣ����ͣ������
#define STATUS_STOP 1
#define STATUS_PAUSE 2
#define STATUS_PLAY 3


//-----------------------------------
typedef struct MusicNode
{
	WORD deviceId;				//�򿪵������ļ����豸id
	wchar_t name[MAX_PATH];		//����������
	struct MusicNode* pre;		//ָ����һ���ڵ�
	struct MusicNode* next;		//ָ����һ���ڵ�
}MusicNode;

//ɨ��Ŀ¼�µ�mp3�ļ������������Ϣ��g_headOfListָ���������
	//directory Ŀ¼��·������������֤��ȷ��,�����ڲ��ж�
	//��������һ�׸����ɹ��򿪣�����1�����򷵻�0
int openDirectory(wchar_t *directory);


//��ӽڵ㵽ĳ�ڵ����
	//node	Ҫ���뵽�ĸ��ڵ���棬�����������ΪNULL
	//newNode ��ӵĽڵ�
void appendNode(MusicNode* node, MusicNode*newNode);

//��ȡ��ǰ��״̬�����š���ͣ��ֹͣ
int getStatus();

//��������
	//deviceId �豸id
int playMusic(WORD deviceId);

//���ò���ģʽ
	//mode ģʽ
void setMode(int mode);

//��õ�ǰ����ģʽ
	//����ֵΪ����ģʽ
int getMode();











