#include "control.h"


//static������ȫ�ֱ��������ڸ��ļ��ɼ�
static Handler g_handlers[MAX_LEN_FOR_HANDLER];  //�洢�ؼ��Ļص�����������
static int g_lenOfHandlers = 0;  //g_handlers����Ԫ�صĸ���


//���ڹ��̺���
LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
	case WM_NCHITTEST:  //����������¼���������ʵ�ִ����϶���
		return winOnNcHitTest(hwnd, lParam);
	case WM_DESTROY:
		//����������Ϣ
		winOnDestroy();
		break;
	case WM_COMMAND:
		//�ؼ���������Ϣ
		return winOnCommand(hwnd, message, wParam, lParam);  //�������ÿؼ��󶨵Ļص�����
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);  //Ĭ�ϵĴ��ڹ��̺���
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

//���������¼�
void winOnDestroy()
{
	//�ͷŰ�ť����Դ
	releaseBmpResource(g_playBtnBmp); 
	releaseBmpResource(g_playBtnBmp2);
	releaseBmpResource(g_prevBtnBmp);
	releaseBmpResource(g_nextBtnBmp);
	releaseBmpResource(g_modeBtnBmp);
	releaseBmpResource(g_xBtnBmp);

	PostQuitMessage(0);  //����WM_QUIT��Ϣ��������Ϣѭ���Ĳ����˳�
}

//�ͷŰ�ť��λͼ��Դ
void releaseBmpResource(ButtonBmp* btnBmp)
{
	for(int i = 0; i < 3; i++)
	{
		DeleteObject(btnBmp->bmps[i]);
	}

	free(btnBmp);
}

//����������¼����������ס�ڶ���һ���������ô����϶�
LRESULT winOnNcHitTest(HWND hWin, LPARAM lParam)
{
	POINT point;
	RECT rect;

	//�����������
	point.x = GET_X_LPARAM(lParam);
	point.y = GET_Y_LPARAM(lParam);
	ScreenToClient(hWin, &point);  //������ת��������ڴ��ڿͻ���������

	//��ȡ���ڿͻ�����������
	GetClientRect(hWin, &rect);

	if(point.y >= rect.top && point.y < rect.top + MOVE_WINDOW_HEIGHT)
	{ //�����߶�ΪMOVE_WINDOW_HEIGHT�����������ƶ�����
		return HTCAPTION;
	}
	else
	{ //����������Ϊ�ǿͻ�����ĵ��
		return HTCLIENT;
	}
}

//�����¼�������ؼ���������Ϣ
LRESULT winOnCommand(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam)
{
	int code;  //֪ͨ��
	HWND hControl;  //�ؼ����
	CallBackFunc func;  //�ؼ����¼�������

	code = HIWORD(wParam);
	hControl = (HWND)lParam; 

	func = getCallBackFunc(hControl);  //��ȡ�ÿؼ����¼�������
	if(func != NULL)
		return func(hControl, code);  //���ú�������ؼ����¼�
	else
		return DefWindowProc(hWin, message, wParam, lParam);
}

//�˳���ť���¼�������
LRESULT quitBtnHandler(HWND hwnd, int code)
{
	if(code == BN_CLICKED)
	{  //��ť�����Ϣ
		HWND hParent = GetParent(hwnd);  //�����ھ���������ť�ĸ�������������
		DestroyWindow(hParent);  //��������������
	}

	return 0;  //�����˳� 
}