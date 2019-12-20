#include "view.h"

ButtonBmp* g_playBtnBmp = NULL;  //���Ű�ť�����ͼƬ
ButtonBmp* g_playBtnBmp2 = NULL;  //��ͣ��ť�����ͼƬ

//��ʼ������
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	buttonInit();  //ע���Զ���İ�ť��


	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = windowProc;  //���ڹ��̺���
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;  //��������

	RegisterClass(&wc);

	HWND hWin = CreateWindowEx(
		0,                    // Optional window styles.
		CLASS_NAME,           // Window class
		WINDOW_TITLE,         // Window text
		WS_OVERLAPPEDWINDOW,  // Window style
		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,       // Parent window
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
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
		50,						//����
		50,						//�߶�
		hWin,                   //�����ھ��
		NULL,                   //�˵��ľ�������Ӵ��ڵı�ʶ��
		(HINSTANCE)GetWindowLong(hWin, GWLP_HINSTANCE),      //Ӧ�ó���ʵ���ľ��
		NULL);*/                //ָ�򴰿ڵĴ�������

	playButtonInit(hWin, hInstance);

	ShowWindow(hWin, nCmdShow);  //��ʾ����
}


void playButtonInit(HWND hParent, HINSTANCE hInstance)
{

	
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_playBtnBmp = btnBmp;
	
	//����ͼƬ��Դ
	
	//δ�����õ�һ�׶���
	//��̬
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_PAUSE_HOVER_PLAY_BUTTON, IMAGE_BITMAP, 
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