#include "control.h"
#include "view.h"
#include <stdlib.h>

//static属性让以下两个全局变量，仅在该文件可见
static Handler g_handlers[MAX_LEN_FOR_HANDLER];  //存储控件的回调函数及其句柄
static int g_lenOfHandlers = 0;  //g_handlers数组元素的个数

//窗口过程函数
LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	int code;  //通知码
	HWND hControl;  //控件句柄
	CallBackFunc func;  //控件的事件处理函数

	PAINTSTRUCT ps;
	HDC hdc;

	switch(uMsg)
	{
	case WM_DESTROY:
		//窗口销毁消息
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		//控件触发的消息
		code = HIWORD(wParam);  //通知码
		hControl = (HWND)lParam;  //控件句柄

		func = getCallBackFunc(hControl);  //获取该控件的事件处理函数
		if(func != NULL)
			return func(hControl, code);
		else
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	case WM_PAINT:
		//窗口重绘消息
		hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
		EndPaint(hwnd, &ps);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);  //默认的回调函数
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