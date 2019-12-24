#pragma once

#include <Windows.h>
#include "view.h"
#include "MyButton.h"
#include <stdlib.h>
#include "MusicControl.h"

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
	//btnBmp �����Ҫ�ͷŵ�ͼƬ��Դ�Ľṹ���ָ��
void releaseBmpResource(ButtonBmp* btnBmp);

//����������¼����������ס�ڶ���һ���������ô����϶�
	//hWin �����ڵľ��
	//lParam �����ڹ��̺����е�lParam����
LRESULT winOnNcHitTest(HWND hWin, LPARAM lParam);


//�����¼�������ؼ���������Ϣ
	//hWin �����ڵľ��
	//message �����ڹ��̺����е�message����
	//wParam �����ڹ��̺����е�wParam����
	//lParam �����ڹ��̺����е�lParam����
LRESULT winOnCommand(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam);

//���ڴ����¼�,��ȡ�豸����Ȳ���
	//hWin �����ڵľ��
void winOnCreate(HWND hWin);

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