#pragma once

//win32api
#include <Windows.h>

//viewģ��
#include "view.h"

//�Զ���İ�ť�ؼ�
#include "MyButton.h"

//��׼�⣬Ҫʹ��malloc����
#include <stdlib.h>

//�������ֵĲ���
#include "MusicControl.h"

/*
��ģ�鸺������߼�
*/

//���ɰ󶨻ص��������¼���
#define MAX_LEN_FOR_HANDLER 64

//�����ڹ��̺���
	//hwnd ���ھ��
	//message ����������Ϣ
	//wParam ���渽����Ϣ
	//lParam ���渽����Ϣ
	//����ϵͳҪ��һ������ֵ
LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); 

//�¼���Ϣ����ѭ��
void eventLoop(); 

//��Ӹ����������б���ʾ���ú�����Ϊ�ص���������traverseAllMusic
	//node �����ڵ�
	//����ֵ����traverseAllMusic������
int addSongToList(MusicNode* node);

//--------------------------
//�ؼ��¼������İ����
//�ص�����������
	//hwnd ���
	//code ֪ͨ��
	//�ú�������ֵ��Ϊ�����ڹ��̺����ķ���ֵ����
typedef LRESULT(*CallBackFunc)(HWND hwnd, int code);

typedef struct Handler  //�洢�ؼ��������ص�����
{
	HWND hwnd;  //�ؼ��ľ��
	CallBackFunc func;  //�ص�����
} Handler;

//���ݿؼ��������ȡ�ص���
	//hwnd �ؼ��ľ��
	//����ֵΪ�ص�����ָ�룬��û�з���NULL
CallBackFunc getCallBackFunc(HWND hwnd); 

//���ؼ��󶨻ص�����
	//hwnd �ؼ��ľ��
	//func �ص�����ָ��
void bindCallBackFunc(HWND hwnd, CallBackFunc func); 

//---------------------
//�����ڹ��̺��������¼��Ĳ������

//���������¼�
void winOnDestroy();

//�ͷŰ�ť��λͼ��Դ
	//btnBmp �����Ҫ�ͷŵ�ͼƬ��Դ�Ľṹ���ָ��
void releaseBmpResource(ButtonBmp* btnBmp);

//����������¼����������ס�ڶ���һ���������ô����϶�
	//hWin �����ڵľ��
	//lParam �����ڹ��̺����е�lParam����
	//�ú�������ֵ��Ϊ�����ڹ��̺����ķ���ֵ����
LRESULT winOnNcHitTest(HWND hWin, LPARAM lParam);


//�����¼�������ؼ���������Ϣ
	//hWin �����ڵľ��
	//message �����ڹ��̺����е�message����
	//wParam �����ڹ��̺����е�wParam����
	//lParam �����ڹ��̺����е�lParam����
	//�ú�������ֵ��Ϊ�����ڹ��̺����ķ���ֵ����
LRESULT winOnCommand(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam);

//���ڴ����¼�,��ȡ�豸����Ȳ���
	//hWin �����ڵľ��
void winOnCreate(HWND hWin);

//WM_NOTIFY�¼�����,���ﴦ���б���¼�
	//hWin �����ھ�ı�
void winOnNotify(HWND hWin);

//---------------------
//�ؼ��Ĵ�����

//�˳���ť���¼�������
	//hwnd ��ť�ľ��
	//code ֪ͨ��
LRESULT quitBtnHandler(HWND hwnd, int code);

//���Ű�ť���¼�������
	//hwnd ��ť�ľ��
	//code ֪ͨ�� 
LRESULT playBtnHandler(HWND hwnd, int code);

//ģʽ��ť���¼�������
	//hwnd ��ť�ľ��
	//code ֪ͨ�� 
LRESULT modeBtnHandler(HWND hwnd, int code);
//------------------------

//û����Ϣʱ���߼���ѭ����ȡ���ֵĽ��ȣ����½���������ʱ������һ��
void progressWhenNoMessage();