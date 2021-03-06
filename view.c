#include "view.h"

ButtonBmp * g_playBtnBmpCur = NULL;		//播放按钮的当前使用的一套图片
ButtonBmp* g_playBtnBmp1 = NULL;		//播放按钮的没有播放时的一套图片
ButtonBmp* g_playBtnBmp2 = NULL;		//播放按钮播放时的一套图片
ButtonBmp* g_nextBtnBmp = NULL;   //下一首按钮的相关图片
ButtonBmp* g_prevBtnBmp = NULL;   //上一首按钮的相关图片
ButtonBmp* g_xBtnBmp = NULL;      //退出按钮的相关图片
ButtonBmp* g_modeBtnBmpCur = NULL;//模式按钮的当前使用的一套相关图片
ButtonBmp* g_modeBtnBmp1 = NULL;  //模式按钮顺序播放使用的相关图片
ButtonBmp* g_modeBtnBmp2 = NULL;  //模式按钮循环播放使用的相关图片
ButtonBmp* g_modeBtnBmp3 = NULL;  //模式按钮随机播放使用的相关图片

HDC g_hdcOfMainWin;			//主窗口的设备句柄
HDC g_hBuffOfMainWin;		//用来缓冲的设备环境
HBITMAP g_hBitmap;			//用来贴图的内存区域
HWND g_hWin;				//主窗口句柄
HWND g_hPlayBtn;            //播放按钮的句柄
HWND g_hSongList;			//歌曲列表的句柄


//初始化窗口
	//hInstance 程序句柄
	//pre		该参数windows不使用
	//pCmdLind	命令行参数
	//nCmdShow	窗口显示的方式
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	buttonInit();          //注册自定义的按钮类
	InitCommonControls();  //初始化window提供的控件


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
		400, 200, WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL,       // 父窗口
		NULL,       // 菜单
		hInstance,  // 程序的实例句柄
		NULL        // 额外参数
	);

	if(hWin == NULL)
		exit(0);

	playButtonInit(hWin, hInstance);        //播放按钮
	nextButtonInit(hWin, hInstance);        //下一首按钮
	prevButtonInit(hWin, hInstance);        //上一首按钮
	xButtonInit(hWin, hInstance);           //关闭窗口按钮
	modeButtonInit(hWin, hInstance);        //模式按钮
	songListInit(hWin, hInstance);			//歌曲列表

	ShowWindow(hWin, nCmdShow);             //显示窗口
}

//创建模式按钮
	//hParent 父窗口句柄
	//hInstance 程序句柄
void modeButtonInit(HWND hParent, HINSTANCE hInstance)
{
	g_modeBtnBmpCur = (ButtonBmp*)malloc(sizeof(ButtonBmp)); //当前界面所需要的图片组
	g_modeBtnBmp1 = (ButtonBmp*)malloc(sizeof(ButtonBmp));
	g_modeBtnBmp2 = (ButtonBmp*)malloc(sizeof(ButtonBmp));
	g_modeBtnBmp3 = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	//加载图片资源

	//循环播放图片
	g_modeBtnBmp1->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_MODE_1_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//鼠标悬停
	g_modeBtnBmp1->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_MODE_1_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//鼠标按下
	g_modeBtnBmp1->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_MODE_1_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);


	//顺序播放图片
	g_modeBtnBmp2->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_MODE_2_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//鼠标悬停
	g_modeBtnBmp2->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_MODE_2_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//鼠标按下
	g_modeBtnBmp2->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_MODE_2_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);


	//随机播放图片
	g_modeBtnBmp3->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_MODE_3_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//鼠标悬停
	g_modeBtnBmp3->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_MODE_3_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//鼠标按下
	g_modeBtnBmp3->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_MODE_3_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);


	memcpy(g_modeBtnBmpCur, g_modeBtnBmp1, sizeof(ButtonBmp));        //初始为循环播放的图片


	HWND hModeBtn = CreateWindow(
		CLASS_MY_BUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,  //WS_CHILD表示这个窗口是某个窗口的子窗口，WS_VISIBLE表示窗口可见（不设置将会不显示）
		POS_X_MODE_BUTTON,
		POS_Y_MODE_BUTTON,
		WIDTH_MODE_BUTTON,
		HEIGHT_MODE_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)g_modeBtnBmpCur   //关于按钮图片的指针，作为参数传入
	);

	//绑定事件处理函数
	bindCallBackFunc(hModeBtn, modeBtnHandler);
}

//创建退出按钮
	//hParent 父窗口句柄
	//hInstance 程序句柄
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
		CLASS_MY_BUTTON,
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

//创建prev按钮
	//hParent 父窗口句柄
	//hInstance 程序句柄
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
		CLASS_MY_BUTTON,
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

	bindCallBackFunc(hPrevBtn, prevBtnHandler); 
}

//创建next按钮
	//hParent 父窗口句柄
	//hInstance 程序句柄
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
		CLASS_MY_BUTTON,
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

	bindCallBackFunc(hNextBtn, nextBtnHandler); 
}

//创建播放按钮
	//hParent 父窗口句柄
	//hInstance 程序句柄
void playButtonInit(HWND hParent, HINSTANCE hInstance)
{
	g_playBtnBmpCur = (ButtonBmp*)malloc(sizeof(ButtonBmp));
	g_playBtnBmp1 = (ButtonBmp*)malloc(sizeof(ButtonBmp));
	g_playBtnBmp2 = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	//加载图片资源
	
	//未播放用的一套动画
	//静态
	g_playBtnBmp1->bmps[BMP_STATIC] = LoadImage(0, BMP_PAUSE_STATIC_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	//鼠标悬停
	g_playBtnBmp1->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_PAUSE_HOVER_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	//鼠标按下
	g_playBtnBmp1->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_MOUSE_DOWN_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);


	//另一套图，播放时用的一套动画
	g_playBtnBmp2->bmps[BMP_STATIC] = LoadImage(0, BMP_PLAY_STATIC_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	g_playBtnBmp2->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_PLAY_HOVER_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	g_playBtnBmp2->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_MOUSE_DOWN_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);  //这张图和第一套的一样

	//选第一套图作为当前的使用的一套图
	//利用内存拷贝的方式把内容复制一份
	memcpy(g_playBtnBmpCur, g_playBtnBmp1, sizeof(ButtonBmp));

	HWND hPlayBtn = CreateWindow(
		CLASS_MY_BUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,
		POS_X_PLAY_BUTTON,
		POS_Y_PLAY_BUTTON,
		WIDTH_PLAY_BUTTON,
		HEIGHT_PLAY_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)g_playBtnBmpCur   //关于按钮图片的指针，作为参数传入
		);


	//绑定按钮点击事件
	bindCallBackFunc(hPlayBtn, playBtnHandler);
}

//创建歌曲列表
	//hParent 父窗口句柄
	//hInstance 程序句柄
void songListInit(HWND hParent, HINSTANCE hInstance)
{
	HWND hSongList = CreateWindow(
		WC_LISTVIEW,
		NULL,
		WS_CHILD |WS_VISIBLE | LBS_NOTIFY,
		POS_X_SONG_LIST,
		POS_Y_SONG_LIST,
		WIDTH_SONG_LIST,
		HEIGHT_SONG_LIST,
		hParent,
		NULL,
		hInstance,
		NULL
	);

	g_hSongList = hSongList;	//保存句柄到全局变量待用

	//设置列表的列（列表的头）
	LV_COLUMN   lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;

	lvc.cx = WIDTH_OF_LIST_COLUMN_1;		//宽度
	lvc.pszText = TEXT_OF_LIST_COLUMN_1;	//表头文字
	ListView_InsertColumn(hSongList, 0, &lvc);

	lvc.cx = WIDTH_OF_LIST_COLUMN_2;		//宽度
	lvc.pszText = TEXT_OF_LIST_COLUMN_2;	//表头文字
	ListView_InsertColumn(hSongList, 1, &lvc);
}

//绘制进度条
	//persent 进度条的百分比  persent为98则表示98%
void drawProgressBar(double persent)
{
	RECT rect;
	HBRUSH bgBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);  //灰色背景
	HBRUSH fgBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);  //白色前景

	rect.left = POS_X_PROGRESS_BAR;
	rect.right = rect.left + WIDTH_PROGRESS_BAR;
	rect.top = POS_Y_PROGRESS_BAR;
	rect.bottom = rect.top + HEIGHT_PROGRESS_BAR;

	int length = (int)(persent * WIDTH_PROGRESS_BAR / 100);

	SelectObject(g_hBuffOfMainWin, g_hBitmap);		//选定一块区域才能开始作画
	FillRect(g_hBuffOfMainWin, &rect, bgBrush);		//绘制背景

	rect.right = rect.left + length;				//进度条的右端位置为左端位置加上长度

	FillRect(g_hBuffOfMainWin, &rect, fgBrush);		//绘制进度条

	//将缓冲的内存拷贝到真正的窗口的区域
	BitBlt(g_hdcOfMainWin, POS_X_PROGRESS_BAR, POS_Y_PROGRESS_BAR, 
		WIDTH_PROGRESS_BAR, HEIGHT_PROGRESS_BAR, g_hBuffOfMainWin,
		POS_X_PROGRESS_BAR, POS_Y_PROGRESS_BAR, SRCCOPY);
}

//切换播放按钮的图片
	//hwnd 按钮句柄
	//status 按钮的状态
void switchPlayBtnBmp(HWND hwnd, int status)
{
	if(status == STATUS_PLAY)
	{ //播放状态
		memcpy(g_playBtnBmpCur, g_playBtnBmp2, sizeof(ButtonBmp));
	}
	else
	{ //暂停状态
		memcpy(g_playBtnBmpCur, g_playBtnBmp1, sizeof(ButtonBmp));
	}

	//刷新按钮
	InvalidateRect(hwnd, NULL, FALSE);
	UpdateWindow(hwnd);
}

//切换模式按钮的图片
	//hwnd 按钮句柄
	//status 按钮的状态
void switchModeBtnBmp(HWND hwnd, int status)
{
	if (status == MODE_LOOP)
	{ //循环播放状态
		memcpy(g_modeBtnBmpCur, g_modeBtnBmp1, sizeof(ButtonBmp));
	}
	else if(status == MODE_ORDER)
	{ //顺序播放状态
		memcpy(g_modeBtnBmpCur, g_modeBtnBmp2, sizeof(ButtonBmp));
	}
	else 
	{ //随机播放状态
		memcpy(g_modeBtnBmpCur, g_modeBtnBmp3, sizeof(ButtonBmp));
	}

	//刷新按钮
	InvalidateRect(hwnd, NULL, FALSE);
	UpdateWindow(hwnd);
}