#include "control.h"
#include "view.h"
#include <stdlib.h>

//static������ȫ�ֱ��������ڸ��ļ��ɼ�
static Handler g_handlers[MAX_LEN_FOR_HANDLER];  //�洢�ؼ��Ļص�����������
static int g_lenOfHandlers = 0;  //g_handlers����Ԫ�صĸ���


//���ڹ��̺���
LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	int code;  //֪ͨ��
	HWND hControl;  //�ؼ����
	CallBackFunc func;  //�ؼ����¼�������

	POINT point;
	RECT rect;

	switch(uMsg)
	{
	case WM_NCHITTEST:  //����������¼���������ʵ�ִ����϶���
		//�����������
		point.x = GET_X_LPARAM(lParam);
		point.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hwnd, &point);  //������ת��������ڴ��ڿͻ���������

		//��ȡ���ڿͻ�����������
		GetClientRect(hwnd, &rect);

		if(point.y >= rect.top && point.y < rect.top + MOVE_WINDOW_HEIGHT)
		{ //�����߶�ΪMOVE_WINDOW_HEIGHT�����������ƶ�����
			return HTCAPTION;
		}
		else
		{ //����������Ϊ�ǿͻ�����ĵ��
			return HTCLIENT;   
		}
	case WM_DESTROY:
		//����������Ϣ
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		//�ؼ���������Ϣ
		code = HIWORD(wParam);  //֪ͨ��
		hControl = (HWND)lParam;  //�ؼ����

		func = getCallBackFunc(hControl);  //��ȡ�ÿؼ����¼�������
		if(func != NULL)
			return func(hControl, code);  //���ú�������ؼ����¼�
		else
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);  //Ĭ�ϵĴ��ڹ��̺���
	}

	return 0;  //�����˳�
}

//�¼���Ϣ����ѭ��
void eventLoop()
{
	MSG msg = { 0 };
	while(msg.message != WM_QUIT)
	{
		//ȡ����Ϣ
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);  //��������Ϣ��ת���ɶ�Ӧ���ַ�����
			DispatchMessage(&msg);  //�ַ���Ϣ�����ڹ��̺���
		}
		else
		{
			//��鵱ǰ�����Ƿ񲥷����
			//���������ϣ�������һ��
		}
	}
}

//���ݿؼ����hwnd����ȡ�ص���������û�з���NULL
CallBackFunc getCallBackFunc(HWND hwnd)
{
	int i;
	for(i = 0; i < g_lenOfHandlers; i++)
	{
		if(g_handlers[i].hwnd == hwnd)
			return g_handlers[i].func;
	}

	return NULL;  //�����ڸÿؼ��Ļص�����
}

//���ؼ�hwnd��func�ص�����
void bindCallBackFunc(HWND hwnd, CallBackFunc func)
{
	if(g_lenOfHandlers < MAX_LEN_FOR_HANDLER)
	{
		g_handlers[g_lenOfHandlers].hwnd = hwnd;
		g_handlers[g_lenOfHandlers].func = func;
		g_lenOfHandlers++;  //���ȵ���1 
	}
	else
	{//���鳬������
		exit(0); 
	}
}