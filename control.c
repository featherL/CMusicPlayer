#include "control.h"


//static������ȫ�ֱ��������ڸ��ļ��ɼ�
static Handler g_handlers[MAX_LEN_FOR_HANDLER];  //�洢�ؼ��Ļص�����������
static int g_lenOfHandlers = 0;  //g_handlers����Ԫ�صĸ���

//�����ڹ��̺���
	//hwnd ���ھ��
	//message ����������Ϣ
	//wParam ���渽����Ϣ
	//lParam ���渽����Ϣ
	//����ϵͳҪ��һ������ֵ
LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
	case WM_CREATE:
		winOnCreate(hwnd);
		break;
	case WM_NCHITTEST:  //����������¼���������ʵ�ִ����϶���
		return winOnNcHitTest(hwnd, lParam);
	case WM_NCDESTROY:
		//����������Ϣ��WM_NCDESTROY���Ӵ��ڶ����ٺ�Ŵ�����
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
			progressWhenNoMessage();
		}
	}
}

//���ݿؼ��������ȡ�ص���
	//hwnd �ؼ��ľ��
	//����ֵΪ�ص�����ָ�룬��û�з���NULL
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

//���ؼ��󶨻ص�����
	//hwnd �ؼ��ľ��
	//func �ص�����ָ��
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

	//���Ű�ť
	releaseBmpResource(g_playBtnBmp1); 
	releaseBmpResource(g_playBtnBmp2);
	free(g_playBtnBmpCur);

	//��һ�ף���һ�װ�ť
	releaseBmpResource(g_prevBtnBmp);
	releaseBmpResource(g_nextBtnBmp);

	//ģʽ��ť
	releaseBmpResource(g_modeBtnBmp1);
	releaseBmpResource(g_modeBtnBmp2);
	releaseBmpResource(g_modeBtnBmp3);
	free(g_modeBtnBmpCur);
	
	//�˳���ť
	releaseBmpResource(g_xBtnBmp);

	//ɾ���ڴ�λͼ
	DeleteObject(g_hBitmap);


	//�ͷ��豸���
	DeleteDC(g_hBuffOfMainWin);
	ReleaseDC(g_hWin, g_hdcOfMainWin);

	
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
	//hWin �����ڵľ��
	//lParam �����ڹ��̺����е�lParam����
	//�ú�������ֵ��Ϊ�����ڹ��̺����ķ���ֵ����
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
	//hWin �����ڵľ��
	//message �����ڹ��̺����е�message����
	//wParam �����ڹ��̺����е�wParam����
	//lParam �����ڹ��̺����е�lParam����
	//�ú�������ֵ��Ϊ�����ڹ��̺����ķ���ֵ����
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

//���ڴ����¼�,��ȡ�豸����Ȳ���
void winOnCreate(HWND hWin)
{
	g_hWin = hWin;
	g_hdcOfMainWin = GetDC(hWin);
	g_hBuffOfMainWin = CreateCompatibleDC(g_hdcOfMainWin);
	g_hBitmap = CreateCompatibleBitmap(g_hdcOfMainWin, WINDOW_WIDTH, WINDOW_HEIGHT);
}

//�˳���ť���¼�������
	//hwnd ��ť�ľ��
	//code ֪ͨ��
LRESULT quitBtnHandler(HWND hwnd, int code)
{
	if(code == BN_CLICKED)
	{  //��ť�����Ϣ
		HWND hParent = GetParent(hwnd);  //�����ھ���������ť�ĸ�������������
		DestroyWindow(hParent);  //��������������
	}

	return 0;  //�����˳� 
}

//û����Ϣʱ���߼���ѭ����ȡ���ֵĽ��ȣ����½���������ʱ������һ��
void progressWhenNoMessage()
{
	static int count = 0;
	static int persent = 0;

	if(count == 100000)
	{
		persent += 1;
		persent = persent % 100;
		drawProgressBar(persent);
		count = 0;
	}

	count++;
}

//���Ű�ť���¼�������
	//hwnd ��ť�ľ��
	//code ֪ͨ��
LRESULT playBtnHandler(HWND hwnd, int code)
{
	static int status = STATUS_PLAY;
	if(code == BN_CLICKED)
	{  //����¼�
		//����
		
		playNext();
		
		//int status = getStatus();

		if(status == STATUS_PLAY)
			status = STATUS_PAUSE;
		else
			status = STATUS_PLAY;

		//�л���ť��ͼƬ
		switchPlayBtnBmp(hwnd, status);
	}

	return 0;
}

//���Ű�ť���¼�������
	//hwnd ��ť�ľ��
	//code ֪ͨ�� 
LRESULT modeBtnHandler(HWND hwnd, int code)
{
	static int status = MODE_ORDER;
	if (code == BN_CLICKED)
	{  //����¼�

		//int status = getStatus();

		if (status == MODE_LOOP)        
			status = MODE_ORDER;
		else if (status == MODE_ORDER)
			status = MODE_RANDOWM;
		else
			status = MODE_LOOP;

		//�л���ť��ͼƬ
		switchModeBtnBmp(hwnd, status);
	}

	return 0;
}