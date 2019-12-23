#pragma once

#include <Windows.h>

//·�������ĺ���
#include <Shlwapi.h> 
#pragma comment(lib,"shlwapi.lib")

#include <stdlib.h>

//mci�ӿ�
#include <mmsystem.h>  
#pragma comment (lib, "winmm.lib")


//-----------------------------------
typedef struct MusicNode
{
	WORD deviceId;				//�򿪵������ļ����豸id
	wchar_t name[MAX_PATH];		//����������
	struct MusicNode* pre;		//ָ����һ���ڵ�
	struct MusicNode* next;		//ָ����һ���ڵ�
}MusicNode;


extern MusicNode* g_headOfList;			//���и����������ͷָ��
extern MusicNode* g_headOfPlaying;		//���Ŷ��������ͷָ��
extern MusicNode* g_curNode;			//��ǰ���ڲ��ŵĸ���

//ɨ��Ŀ¼�µ�mp3�ļ������������Ϣ��g_headOfListָ���������
	//directory Ŀ¼��·������������֤��ȷ��,�����ڲ��ж�
	//��������һ�׸����ɹ��򿪣�����1�����򷵻�0
int openDirectory(wchar_t *directory);


//��ӽڵ㵽ĳ�ڵ����
	//node	Ҫ���뵽�ĸ��ڵ���棬�����������ΪNULL
	//newNode ��ӵĽڵ�
void appendNode(MusicNode* node, MusicNode*newNode);
