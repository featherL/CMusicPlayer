#pragma once

//win32api
#include <Windows.h>

//·�������ĺ���
#include <Shlwapi.h> 
#pragma comment(lib,"shlwapi.lib")

//��׼�⣬Ҫʹ��malloc����
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
	DWORD length;				//�����ĳ���
	wchar_t name[MAX_PATH];		//����������
	struct MusicNode* pre;		//ָ����һ���ڵ�
	struct MusicNode* next;		//ָ����һ���ڵ�
}MusicNode;

//ɨ��Ŀ¼�µ�mp3�ļ������������Ϣ��g_headOfListָ���������
	//directory Ŀ¼��·������������֤��ȷ��,�����ڲ��ж�
	//��������һ�׸����ɹ��򿪣�����1�����򷵻�0
int openDirectory(wchar_t *directory);

//-------------------------------------------
//���������õĻص�����������
	//node �������Ľڵ�
	//�ص���������ֵΪ1��ʾ��������������ֹͣ����
typedef int (*TraverseCallBack)(MusicNode* node);

//��������������ÿ���ڵ���ûص�����
	//callBackFunc �ص�����
void traverse(TraverseCallBack callBackFunc);

//-------------------------------------------
//��ӽڵ㵽ĳ�ڵ����
	//node	Ҫ���뵽�ĸ��ڵ���棬�����������ΪNULL
	//newNode ��ӵĽڵ�
void appendNode(MusicNode* node, MusicNode*newNode);

//�ͷ�ͷָ��ָ�����������нڵ�
	//list ָ��ͷָ�������ָ��(ָ���ָ�룡ָ���ָ�룡ָ���ָ��!)
void freeList(MusicNode** list);

//��ȡ��ǰ��״̬
	//����ֵΪ��ǰ״̬��ȡֵΪSTATUS_STOP��STATUS_PAUSE��STATUS_PLAY
int getStatus();

//��������
	//deviceId �豸id
	//���ųɹ�����1�����򷵻�0
int playMusic(WORD deviceId);

//������һ������
	//�ɹ�����1�����򷵻�0
int playNext();

//ѭ���л�����ģʽ
	//�����л����ģʽ
int switchMode();

//��ͣ��ǰ��������
	//�ɹ�����1�����򷵻�0
int pauseCurrentMusic();

//�ָ���ǰ��������
	//�ɹ�����1�����򷵻�0
int resumeCurrentMusic();

//��ȡ��ǰ�������Ž���
	//����ֵ��ǰ���ŵ�λ�ã�����ǰ�޸������Ż���ͣ���򷵻�0
DWORD getCurrentMusicPos();

//��ȡ��ǰ�����ĳ���
	//����ֵΪ��ǰ�����ĳ��ȣ�����ǰ�޸������Ż�����ͣ���򷵻�1
DWORD getCurrentMusicLenght();

//ֹͣ��ǰ��������
	//�ɹ�����1�����򷵻�0
int stopCurrentMusic();


