#include "view.h"

ButtonBmp* g_playBtnBmp = NULL;  //播放按钮的相关图片
ButtonBmp* g_playBtnBmp2 = NULL;  //暂停按钮的相关图片
ButtonBmp* g_nextBtnBmp = NULL;  //下一首按钮的相关图片
ButtonBmp* g_prevBtnBmp = NULL;  //上一首按钮的相关图片
ButtonBmp* g_xBtnBmp = NULL;  //退出按钮的相关图片
ButtonBmp* g_modeBtnBmp = NULL;  //模式按钮的相关图片


//初始化窗口
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	buttonInit();  //注册自定义的按钮类


	WNDCLASSEX wc = { 0 };
	wc.hCursor = LoadCursor(0, IDC_ARROW);  //光标的样式
	wc.cbSize = sizeof(WNDCLASSEX);  //结构体的大小
	wc.hbrBackground = (HBRUSH)GetStockBrush(BLACK_BRUSH);  //背景黑色
	wc.lpfnWndProc = windowProc;  //窗口过程函数
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;  //窗口类名

	RegisterClassEx(&wc);

	HWND hWin = CreateWindow(
		CLASS_NAME,           // 窗口类名
		WINDOW_TITLE,         // 窗口标题
		WS_POPUP,  // 窗口样式：没有标题栏，没有边框（不可调整大小）
		// 窗口位置（默认），窗口大小
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL,       // 父窗口
		NULL,       // 菜单
		hInstance,  // 程序的实例句柄
		NULL        // 额外参数
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

	playButtonInit(hWin, hInstance);        //播放按钮
	nextButtonInit(hWin, hInstance);        //下一首按钮
	prevButtonInit(hWin, hInstance);        //上一首按钮
	xButtonInit(hWin, hInstance);           //关闭窗口按钮
	modeButtonInit(hWin, hInstance);        //模式按钮

	ShowWindow(hWin, nCmdShow);  //显示窗口
}


void modeButtonInit(HWND hParent, HINSTANCE hInstance)
{
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_modeBtnBmp = btnBmp;

	//加载图片资源

	//静态
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_MODE_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);

	//鼠标悬停
	btnBmp->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_MODE_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);

	//鼠标按下
	btnBmp->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_MODE_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);


	HWND hModeBtn = CreateWindow(
		CLASS_MYBUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,
		POS_X_MODE_BUTTON,
		POS_Y_MODE_BUTTON,
		WIDTH_MODE_BUTTON,
		HEIGHT_MODE_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)btnBmp   //关于按钮图片的指针，作为参数传入
	);

	//bindCallBackFunc(hModeBtn, func); 
}


void xButtonInit(HWND hParent, HINSTANCE hInstance)
{
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_xBtnBmp = btnBmp;

	//加载图片资源

	//静态
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_X_BUTTON, IMAGE_BITMAP,
		WIDTH_X_BUTTON, HEIGHT_X_BUTTON, LR_LOADFROMFILE);

	//鼠标悬停
	btnBmp->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_X_BUTTON, IMAGE_BITMAP,
		WIDTH_X_BUTTON, HEIGHT_X_BUTTON, LR_LOADFROMFILE);

	//鼠标按下
	btnBmp->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_X_BUTTON, IMAGE_BITMAP,
		WIDTH_X_BUTTON, HEIGHT_X_BUTTON, LR_LOADFROMFILE);


	HWND hXBtn = CreateWindow(
		CLASS_MYBUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,
		POS_X_X_BUTTON,
		POS_Y_X_BUTTON,
		WIDTH_X_BUTTON,
		HEIGHT_X_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)btnBmp   //关于按钮图片的指针，作为参数传入
	);


	bindCallBackFunc(hXBtn, quitBtnHandler);            
}


void prevButtonInit(HWND hParent, HINSTANCE hInstance)
{
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_prevBtnBmp = btnBmp;

	//加载图片资源

	//静态
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_PREV_BUTTON, IMAGE_BITMAP,
		WIDTH_PREV_BUTTON, HEIGHT_PREV_BUTTON, LR_LOADFROMFILE);

	//鼠标悬停
	btnBmp->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_PREV_BUTTON, IMAGE_BITMAP,
		WIDTH_PREV_BUTTON, HEIGHT_PREV_BUTTON, LR_LOADFROMFILE);

	//鼠标按下
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
		(LPARAM)btnBmp   //关于按钮图片的指针，作为参数传入
	);

	//bindCallBackFunc(hPrevBtn, func); 
}


void nextButtonInit(HWND hParent, HINSTANCE hInstance) 
{
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_nextBtnBmp = btnBmp;

	//加载图片资源

	//静态
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_NEXT_BUTTON, IMAGE_BITMAP,
		WIDTH_NEXT_BUTTON, HEIGHT_NEXT_BUTTON, LR_LOADFROMFILE);

	//鼠标悬停
	btnBmp->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_NEXT_BUTTON, IMAGE_BITMAP,
		WIDTH_NEXT_BUTTON, HEIGHT_NEXT_BUTTON, LR_LOADFROMFILE);

	//鼠标按下
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
		(LPARAM)btnBmp   //关于按钮图片的指针，作为参数传入
	);

	//bindCallBackFunc(hNextBtn, func); 
}


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

	g_playBtnBmp2->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_MOUSE_DOWN_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);  //这张图和第一套的一样


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
	//bindCallBackFunc(hPlayBtn, func); 
}
