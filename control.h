#pragma once

#include <Windows.h>
#include "view.h"
#include "MyButton.h"
#include <stdlib.h>

/*
��ģ�鸺������߼�
*/

//���ɰ󶨻ص��������¼���
#define MAX_LEN_FOR_HANDLER 64

//���ڹ��̺���
LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); 

//�¼���Ϣ����ѭ��
void eventLoop();  

//--------------------------
//�ؼ��¼������İ����
//�ص�����������
typedef LRESULT(*CallBackFunc)(HWND hwnd, int code);

typedef struct Handler  //�洢�ؼ��������ص�����
{
	HWND hwnd;  //�ؼ��ľ��
	CallBackFunc func;  //�ص�����
} Handler;

//���ݿؼ����hwnd����ȡ�ص���������û�з���NULL
CallBackFunc getCallBackFunc(HWND hwnd); 

//���ؼ�hwnd��func�ص�����
void bindCallBackFunc(HWND hwnd, CallBackFunc func); 

//---------------------
//�����ڹ��̺��������¼��Ĳ������

//���������¼�
void winOnDestroy();

//�ͷŰ�ť��λͼ��Դ
void releaseBmpResource(ButtonBmp* btnBmp);

//����������¼����������ס�ڶ���һ���������ô����϶�
LRESULT winOnNcHitTest(HWND hWin, LPARAM lParam);


//�����¼�������ؼ���������Ϣ
LRESULT winOnCommand(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam);

//---------------------
//�ؼ��Ĵ�����

//�˳���ť���¼�������
LRESULT quitBtnHandler(HWND hwnd, int code);

//------------------------