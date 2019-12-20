#include "view.h"

ButtonBmp* g_playBtnBmp = NULL;  //���Ű�ť�����ͼƬ
ButtonBmp* g_playBtnBmp2 = NULL;  //��ͣ��ť�����ͼƬ
ButtonBmp* g_nextBtnBmp = NULL;  //��һ�װ�ť�����ͼƬ
ButtonBmp* g_prevBtnBmp = NULL;  //��һ�װ�ť�����ͼƬ


//��ʼ������
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	buttonInit();  //ע���Զ���İ�ť��


	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = windowProc;  //���ڹ��̺���
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;  //��������

	RegisterClass(&wc);

	HWND hWin = CreateWindow(
		CLASS_NAME,           // ��������
		WINDOW_TITLE,         // ���ڱ���
		WS_POPUP,  // ������ʽ��û�б�������û�б߿򣨲��ɵ�����С��
		// ����λ�ã�Ĭ�ϣ������ڴ�С
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL,       // ������
		NULL,       // �˵�
		hInstance,  // �����ʵ�����
		NULL        // �������
	);

	if(hWin == NULL)
		exit(0);


	//����һ����ť
	/*HWND hButton = CreateWindow(
		CLASS_MYBUTTON,//
		L"|<",                  //�ı�����
		WS_CHILD | WS_VISIBLE,
		CW_USEDEFAULT,          //ˮƽλ��
		CW_USEDEFAULT,			//��ֱλ��
		50,						//���
		50,						//�߶�
		hWin,                   //�����ھ��
		NULL,                   //�˵��ľ�������Ӵ��ڵı�ʶ��
		(HINSTANCE)GetWindowLong(hWin, GWLP_HINSTANCE),      //Ӧ�ó���ʵ���ľ��
		NULL);*/                //ָ�򴰿ڵĴ�������

	playButtonInit(hWin, hInstance);
	nextButtonInit(hWin, hInstance);
	prevButtonInit(hWin, hInstance);

	ShowWindow(hWin, nCmdShow);  //��ʾ����
}


void prevButtonInit(HWND hParent, HINSTANCE hInstance)
{
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_prevBtnBmp = btnBmp;

	//����ͼƬ��Դ

	//��̬
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_PREV_BUTTON, IMAGE_BITMAP,
		WIDTH_PREV_BUTTON, HEIGHT_PREV_BUTTON, LR_LOADFROMFILE);

	//�����ͣ
	btnBmp->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_PREV_BUTTON, IMAGE_BITMAP,
		WIDTH_PREV_BUTTON, HEIGHT_PREV_BUTTON, LR_LOADFROMFILE);

	//��갴��
	btnBmp->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_PREV_BUTTON, IMAGE_BITMAP,
		WIDTH_PREV_BUTTON, HEIGHT_PREV_BUTTON, LR_LOADFROMFILE);


	HWND hPrevBtn = CreateWindow(
		CLASS_MYBUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,
		POS_X_PREV_BUTTON,
		POS_Y_PREV_BUTTON,
		WIDTH_PREV_BUTTON,
		HEIGHT_PREV_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)btnBmp   //���ڰ�ťͼƬ��ָ�룬��Ϊ��������
	);
}


void nextButtonInit(HWND hParent, HINSTANCE hInstance) 
{
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_nextBtnBmp = btnBmp;

	//����ͼƬ��Դ

	//��̬
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_NEXT_BUTTON, IMAGE_BITMAP,
		WIDTH_NEXT_BUTTON, HEIGHT_NEXT_BUTTON, LR_LOADFROMFILE);

	//�����ͣ
	btnBmp->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_NEXT_BUTTON, IMAGE_BITMAP,
		WIDTH_NEXT_BUTTON, HEIGHT_NEXT_BUTTON, LR_LOADFROMFILE);

	//��갴��
	btnBmp->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_NEXT_BUTTON, IMAGE_BITMAP,
		WIDTH_NEXT_BUTTON, HEIGHT_NEXT_BUTTON, LR_LOADFROMFILE);


	HWND hNextBtn = CreateWindow(
		CLASS_MYBUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,
		POS_X_NEXT_BUTTON,
		POS_Y_NEXT_BUTTON,
		WIDTH_NEXT_BUTTON,
		HEIGHT_NEXT_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)btnBmp   //���ڰ�ťͼƬ��ָ�룬��Ϊ��������
	);
}


void playButtonInit(HWND hParent, HINSTANCE hInstance)
{

	
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_playBtnBmp = btnBmp;
	
	//����ͼƬ��Դ
	
	//δ�����õ�һ�׶���
	//��̬
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_PAUSE_STATIC_PLAY_BUTTON, IMAGE_BITMAP, 
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	//�����ͣ
	btnBmp->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_PAUSE_HOVER_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	//��갴��
	btnBmp->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_MOUSE_DOWN_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);


	//��һ��ͼ������ʱ�õ�һ�׶���
	g_playBtnBmp2 = (ButtonBmp*)malloc(sizeof(ButtonBmp));
	g_playBtnBmp2->bmps[BMP_STATIC] = LoadImage(0, BMP_PLAY_STATIC_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	g_playBtnBmp2->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_PLAY_HOVER_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);


	HWND hPlayBtn = CreateWindow(
		CLASS_MYBUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,
		POS_X_PLAY_BUTTON,
		POS_Y_PLAY_BUTTON,
		WIDTH_PLAY_BUTTON,
		HEIGHT_PLAY_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)btnBmp   //���ڰ�ťͼƬ��ָ�룬��Ϊ��������
		);


	//�󶨰�ť����¼�

}