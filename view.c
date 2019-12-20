#include "view.h"

ButtonBmp* g_playBtnBmp = NULL;  //播放按钮的相关图片
ButtonBmp* g_playBtnBmp2 = NULL;  //暂停按钮的相关图片

//初始化窗口
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	buttonInit();  //注册自定义的按钮类


	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = windowProc;  //窗口过程函数
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;  //窗口类名

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


	//创建一个按钮
	/*HWND hButton = CreateWindow(
		CLASS_MYBUTTON,//
		L"|<",                  //文本内容
		WS_CHILD | WS_VISIBLE,
		CW_USEDEFAULT,          //水平位置
		CW_USEDEFAULT,			//垂直位置
		50,						//宽度
		50,						//高度
		hWin,                   //父窗口句柄
		NULL,                   //菜单的句柄或是子窗口的标识符
		(HINSTANCE)GetWindowLong(hWin, GWLP_HINSTANCE),      //应用程序实例的句柄
		NULL);*/                //指向窗口的创建数据

	playButtonInit(hWin, hInstance);
	//nextButtonInit(hWin, hInstance);

	ShowWindow(hWin, nCmdShow);  //显示窗口
}


//void nextButtonInit(HWND hParent, HINSTANCE hInstance) 
//{
//	HWND hPlayBtn = CreateWindow(
//		CLASS_MYBUTTON,
//		NULL,
//		WS_CHILD | WS_VISIBLE,
//		POS_X_PLAY_BUTTON,
//		POS_Y_PLAY_BUTTON,
//		WIDTH_PLAY_BUTTON,
//		HEIGHT_PLAY_BUTTON,
//		hParent,
//		NULL,
//		hInstance,
//		(LPARAM)btnBmp   //关于按钮图片的指针，作为参数传入
//	);
//}


void playButtonInit(HWND hParent, HINSTANCE hInstance)
{

	
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_playBtnBmp = btnBmp;
	
	//加载图片资源
	
	//未播放用的一套动画
	//静态
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_PAUSE_STATIC_PLAY_BUTTON, IMAGE_BITMAP, 
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	//鼠标悬停
	btnBmp->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_PAUSE_HOVER_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	//鼠标按下
	btnBmp->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_MOUSE_DOWN_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);


	//另一套图，播放时用的一套动画
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
		(LPARAM)btnBmp   //关于按钮图片的指针，作为参数传入
		);


	//绑定按钮点击事件

}