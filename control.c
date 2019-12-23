#include "control.h"


//static属性让全局变量，仅在该文件可见
static Handler g_handlers[MAX_LEN_FOR_HANDLER];  //存储控件的回调函数及其句柄
static int g_lenOfHandlers = 0;  //g_handlers数组元素的个数

//窗口过程函数
LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
	case WM_CREATE:
		winOnCreate(hwnd);
		break;
	case WM_NCHITTEST:  //鼠标点击测试事件（可用于实现窗口拖动）
		return winOnNcHitTest(hwnd, lParam);
	case WM_NCDESTROY:
		//窗口销毁消息，WM_NCDESTROY是子窗口都销毁后才触发的
		winOnDestroy();
		break;
	case WM_COMMAND:
		//控件触发的消息
		return winOnCommand(hwnd, message, wParam, lParam);  //里面会调用控件绑定的回调函数
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);  //默认的窗口过程函数
	}

	return 0;  //正常退出
}

//事件消息处理循环
void eventLoop()
{
	MSG msg = { 0 };
	while(msg.message != WM_QUIT)
	{
		//取出消息
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);  //将按键消息码转换成对应的字符编码
			DispatchMessage(&msg);  //分发消息给窗口过程函数
		}
		else
		{
			//检查当前歌曲是否播放完毕
			//如果播放完毕，播放下一首
			progressWhenNoMessage();
		}
	}
}

//根据控件句柄hwnd，获取回调函数，若没有返回NULL
CallBackFunc getCallBackFunc(HWND hwnd)
{
	int i;
	for(i = 0; i < g_lenOfHandlers; i++)
	{
		if(g_handlers[i].hwnd == hwnd)
			return g_handlers[i].func;
	}

	return NULL;  //不存在该控件的回调函数
}

//给控件hwnd绑定func回调函数
void bindCallBackFunc(HWND hwnd, CallBackFunc func)
{
	if(g_lenOfHandlers < MAX_LEN_FOR_HANDLER)
	{
		g_handlers[g_lenOfHandlers].hwnd = hwnd;
		g_handlers[g_lenOfHandlers].func = func;
		g_lenOfHandlers++;  //长度递增1 
	}
	else
	{//数组超过上限
		exit(0); 
	}
}

//窗口销毁事件
void winOnDestroy()
{
	//释放按钮的资源
	releaseBmpResource(g_playBtnBmp); 
	releaseBmpResource(g_playBtnBmp2);
	releaseBmpResource(g_prevBtnBmp);
	releaseBmpResource(g_nextBtnBmp);
	releaseBmpResource(g_modeBtnBmp);
	releaseBmpResource(g_xBtnBmp);

	//删除内存位图
	DeleteObject(g_hBitmap);


	//释放设备句柄
	DeleteDC(g_hBuffOfMainWin);
	ReleaseDC(g_hWin, g_hdcOfMainWin);


	PostQuitMessage(0);  //发送WM_QUIT消息，这样消息循环的才能退出
}

//释放按钮的位图资源
void releaseBmpResource(ButtonBmp* btnBmp)
{
	for(int i = 0; i < 3; i++)
	{
		DeleteObject(btnBmp->bmps[i]);
	}

	free(btnBmp);
}

//鼠标点击测试事件，当点击按住在顶部一定的区域，让窗口拖动
LRESULT winOnNcHitTest(HWND hWin, LPARAM lParam)
{
	POINT point;
	RECT rect;

	//鼠标点击的坐标
	point.x = GET_X_LPARAM(lParam);
	point.y = GET_Y_LPARAM(lParam);
	ScreenToClient(hWin, &point);  //讲坐标转换成相对于窗口客户区的坐标

	//获取窗口客户区矩形区域
	GetClientRect(hWin, &rect);

	if(point.y >= rect.top && point.y < rect.top + MOVE_WINDOW_HEIGHT)
	{ //顶部高度为MOVE_WINDOW_HEIGHT的区域用于移动窗口
		return HTCAPTION;
	}
	else
	{ //其它区域认为是客户区域的点击
		return HTCLIENT;
	}
}

//命令事件，处理控件发来的消息
LRESULT winOnCommand(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam)
{
	int code;  //通知码
	HWND hControl;  //控件句柄
	CallBackFunc func;  //控件的事件处理函数

	code = HIWORD(wParam);
	hControl = (HWND)lParam; 

	func = getCallBackFunc(hControl);  //获取该控件的事件处理函数
	if(func != NULL)
		return func(hControl, code);  //调用函数处理控件的事件
	else
		return DefWindowProc(hWin, message, wParam, lParam);
}

//窗口创建事件,获取设备句柄等操作
void winOnCreate(HWND hWin)
{
	g_hWin = hWin;
	g_hdcOfMainWin = GetDC(hWin);
	g_hBuffOfMainWin = CreateCompatibleDC(g_hdcOfMainWin);
	g_hBitmap = CreateCompatibleBitmap(g_hdcOfMainWin, WINDOW_WIDTH, WINDOW_HEIGHT);
}

//退出按钮的事件处理函数
LRESULT quitBtnHandler(HWND hwnd, int code)
{
	if(code == BN_CLICKED)
	{  //按钮点击消息
		HWND hParent = GetParent(hwnd);  //父窗口句柄，这个按钮的父窗口是主窗口
		DestroyWindow(hParent);  //销毁整个主窗口
	}

	return 0;  //正常退出 
}

//没有消息时的逻辑，循环获取音乐的进度，更新进度条，及时播放下一首
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