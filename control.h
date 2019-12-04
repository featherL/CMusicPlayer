#pragma once

#include <Windows.h>

/*
��ģ�鸺������߼�
*/

//���ɰ󶨻ص��������¼���
#define MAX_LEN_FOR_HANDLER 64

//�ص�����������
typedef LRESULT (*CallBackFunc)(HWND hwnd, int code);

typedef struct Handler  //�洢�ؼ��������ص�����
{
	HWND hwnd;  //�ؼ��ľ��
	CallBackFunc func;  //�ص�����
} Handler;

//���ڹ��̺���
LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

//�¼���Ϣ����ѭ��
void eventLoop();  

//���ݿؼ����hwnd����ȡ�ص���������û�з���NULL
CallBackFunc getCallBackFunc(HWND hwnd); 

//���ؼ�hwnd��func�ص�����
void bindCallBackFunc(HWND hwnd, CallBackFunc func); 
