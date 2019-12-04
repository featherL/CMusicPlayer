#pragma once

#include <Windows.h>

/*
该模块负责代码逻辑
*/

//最大可绑定回调函数的事件数
#define MAX_LEN_FOR_HANDLER 64

//回调函数的类型
typedef LRESULT (*CallBackFunc)(HWND hwnd, int code);

typedef struct Handler  //存储控件句柄与其回调函数
{
	HWND hwnd;  //控件的句柄
	CallBackFunc func;  //回调函数
} Handler;

//窗口过程函数
LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

//事件消息处理循环
void eventLoop();  

//根据控件句柄hwnd，获取回调函数，若没有返回NULL
CallBackFunc getCallBackFunc(HWND hwnd); 

//给控件hwnd绑定func回调函数
void bindCallBackFunc(HWND hwnd, CallBackFunc func); 
